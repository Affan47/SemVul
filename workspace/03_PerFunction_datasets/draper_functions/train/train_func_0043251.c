cash_out(PG_FUNCTION_ARGS)
{
	Cash		value = PG_GETARG_CASH(0);
	char	   *result;
	char		buf[128];
	char	   *bufptr;
	bool		minus = false;
	int			digit_pos;
	int			points,
				mon_group;
	char		dsymbol;
	const char *ssymbol,
			   *csymbol,
			   *nsymbol;
	char		convention;
	struct lconv *lconvert = PGLC_localeconv();


	points = lconvert->frac_digits;
	if (points < 0 || points > 10)
		points = 2;


	mon_group = *lconvert->mon_grouping;
	if (mon_group <= 0 || mon_group > 6)
		mon_group = 3;

	convention = lconvert->n_sign_posn;


	if (*lconvert->mon_decimal_point != '\0' &&
		lconvert->mon_decimal_point[1] == '\0')
		dsymbol = *lconvert->mon_decimal_point;
	else
		dsymbol = '.';
	if (*lconvert->mon_thousands_sep != '\0')
		ssymbol = lconvert->mon_thousands_sep;
	else
		ssymbol = (dsymbol != ',') ? "," : ".";
	csymbol = (*lconvert->currency_symbol != '\0') ? lconvert->currency_symbol : "$";
	nsymbol = (*lconvert->negative_sign != '\0') ? lconvert->negative_sign : "-";


	if (value < 0)
	{
		minus = true;
		value = -value;
	}


	bufptr = buf + sizeof(buf) - 1;
	*bufptr = '\0';


	digit_pos = points;
	do
	{
		if (points && digit_pos == 0)
		{

			*(--bufptr) = dsymbol;
		}
		else if (digit_pos < points && (digit_pos % mon_group) == 0)
		{

			bufptr -= strlen(ssymbol);
			memcpy(bufptr, ssymbol, strlen(ssymbol));
		}

		*(--bufptr) = ((uint64) value % 10) + '0';
		value = ((uint64) value) / 10;
		digit_pos--;
	} while (value || digit_pos >= 0);


	bufptr -= strlen(csymbol);
	memcpy(bufptr, csymbol, strlen(csymbol));


	if (minus)
	{
		result = palloc(strlen(bufptr) + strlen(nsymbol) + 3);


		if (convention == 0)
			sprintf(result, "(%s)", bufptr);
		else if (convention == 2)
			sprintf(result, "%s%s", bufptr, nsymbol);
		else
			sprintf(result, "%s%s", nsymbol, bufptr);
	}
	else
	{

		result = pstrdup(bufptr);
	}

	PG_RETURN_CSTRING(result);
}
