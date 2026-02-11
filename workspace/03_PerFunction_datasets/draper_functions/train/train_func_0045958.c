determine_date_style (const gchar *str, guint year, guint month, guint day, GDateDMY *out_first,
		      GDateDMY *out_second, GDateDMY *out_third, gchar *out_sep)
{
	if (!str)
		return FALSE;

	guint nb;
	const gchar *ptr;
	GDateDMY order[3];
	gchar sep;


	for (nb = 0, ptr = str; *ptr; ptr++) {
		if ((*ptr <= '9') && (*ptr >= '0'))
			nb = nb * 10 + (*ptr - '0');
		else
			break;
	}
	if (nb == year)
		order[0] = G_DATE_YEAR;
	else if (nb == month)
		order[0] = G_DATE_MONTH;
	else if (nb == day)
		order[0] = G_DATE_DAY;
	else if (nb == year % 100)
		order[0] = G_DATE_YEAR;
	else
		return FALSE;


	sep = *ptr;
	if (!sep)
		return FALSE;


	for (nb = 0, ptr++; *ptr; ptr++) {
		if ((*ptr <= '9') && (*ptr >= '0'))
			nb = nb * 10 + (*ptr - '0');
		else
			break;
	}
	if (nb == year)
		order[1] = G_DATE_YEAR;
	else if (nb == month)
		order[1] = G_DATE_MONTH;
	else if (nb == day)
		order[1] = G_DATE_DAY;
	else if (nb == year % 100)
		order[1] = G_DATE_YEAR;
	else
		return FALSE;

	if (sep != *ptr)
		return FALSE;


	for (nb = 0, ptr++; *ptr; ptr++) {
		if ((*ptr <= '9') && (*ptr >= '0'))
			nb = nb * 10 + (*ptr - '0');
		else
			break;
	}
	if (nb == year)
		order[2] = G_DATE_YEAR;
	else if (nb == month)
		order[2] = G_DATE_MONTH;
	else if (nb == day)
		order[2] = G_DATE_DAY;
	else if (nb == year % 100)
		order[2] = G_DATE_YEAR;
	else
		return FALSE;


	if (out_first)
		*out_first = order [0];
	if (out_second)
		*out_second = order [1];
	if (out_third)
		*out_third = order [2];
	if (out_sep)
		*out_sep = sep;


	return TRUE;
}
