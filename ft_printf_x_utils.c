/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:36:32 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/26 13:24:58 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				ft_printf_hex(unsigned int hex, t_prnt **t_arg)
{
	if (hex < 10)
		return ((char)hex + '0');
	else if (hex == 10)
		return (((*t_arg)->arg == 'x' || (*t_arg)->arg == 'p') ? 'a' : 'A');
	else if (hex == 11)
		return (((*t_arg)->arg == 'x' || (*t_arg)->arg == 'p') ? 'b' : 'B');
	else if (hex == 12)
		return (((*t_arg)->arg == 'x' || (*t_arg)->arg == 'p') ? 'c' : 'C');
	else if (hex == 13)
		return (((*t_arg)->arg == 'x' || (*t_arg)->arg == 'p') ? 'd' : 'D');
	else if (hex == 14)
		return (((*t_arg)->arg == 'x' || (*t_arg)->arg == 'p') ? 'e' : 'E');
	else if (hex == 15)
		return (((*t_arg)->arg == 'x' || (*t_arg)->arg == 'p') ? 'f' : 'F');
	return (0);
}

static char			*ft_hex_rev(char *revhex, int i)
{
	char	*hex;
	int		n;

	n = 0;
	if (!(hex = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i--;
	while (i >= 0)
	{
		hex[n] = revhex[i];
		n++;
		i--;
	}
	hex[n] = '\0';
	return (hex);
}

static char			*ft_hex_x(unsigned int hexin, t_prnt **t_args)
{
	char	*hex;
	char	*revhex;
	int		i;

	i = 0;
	if (hexin == 0)
	{
		if (!(hex = (char *)malloc(2 * sizeof(char))))
			return (NULL);
		hex[0] = '0';
		hex[1] = 0;
		return (hex);
	}
	if (!(revhex = (char *)malloc(16 * sizeof(char))))
		return (NULL);
	while (hexin > 0)
	{
		revhex[i] = ft_printf_hex(hexin % 16, t_args);
		hexin /= 16;
		i++;
	}
	revhex[i] = 0;
	hex = ft_hex_rev(revhex, i);
	free(revhex);
	return (hex);
}

int					ft_printf_h(t_prnt **l_args, va_list args, int point)
{
	char	*num;
	int		i;

	if (!(num = ft_hex_x(va_arg(args, unsigned int), l_args)))
		return (-1);
	while (num[point] != '\0')
		point++;
	if ((*l_args)->acacy > (-1))
	{
		if ((*num) == '0' && (*l_args)->acacy == 0)
			point = 0;
		point = acacy_d((*l_args)->acacy, point, &num);
	}
	if ((*l_args)->widht > point && (*l_args)->flag != '-')
		return (widht_d((*l_args)->widht, point, &num, l_args));
	else if ((*l_args)->widht > point && (*l_args)->flag == '-')
		return (widht_d_minus((*l_args)->widht, point, num));
	else
	{
		i = write(1, num, point);
		free(num);
		return (i);
	}
	return (0);
}
