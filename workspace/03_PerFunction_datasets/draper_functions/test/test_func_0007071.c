int8_to_char(PG_FUNCTION_ARGS)
{
	int64		value = PG_GETARG_INT64(0);
	text	   *fmt = PG_GETARG_TEXT_P(1);
	NUMDesc		Num;
	FormatNode *format;
	text	   *result;
	bool		shouldFree;
	int			out_pre_spaces = 0,
				sign = 0;
	char	   *numstr,
			   *orgnum;

	NUM_TOCHAR_prepare;


	if (IS_ROMAN(&Num))
	{

		numstr = orgnum = int_to_roman(DatumGetInt32(
						  DirectFunctionCall1(int84, Int64GetDatum(value))));
	}
	else if (IS_EEEE(&Num))
	{

		Numeric		val;

		val = DatumGetNumeric(DirectFunctionCall1(int8_numeric,
												  Int64GetDatum(value)));
		orgnum = numeric_out_sci(val, Num.post);


		if (*orgnum != '-')
		{
			numstr = (char *) palloc(strlen(orgnum) + 2);
			*numstr = ' ';
			strcpy(numstr + 1, orgnum);
		}
		else
		{
			numstr = orgnum;
		}
	}
	else
	{
		int			numstr_pre_len;

		if (IS_MULTI(&Num))
		{
			double		multi = pow((double) 10, (double) Num.multi);

			value = DatumGetInt64(DirectFunctionCall2(int8mul,
													  Int64GetDatum(value),
												   DirectFunctionCall1(dtoi8,
													Float8GetDatum(multi))));
			Num.pre += Num.multi;
		}

		orgnum = DatumGetCString(DirectFunctionCall1(int8out,
													 Int64GetDatum(value)));

		if (*orgnum == '-')
		{
			sign = '-';
			orgnum++;
		}
		else
			sign = '+';

		numstr_pre_len = strlen(orgnum);


		if (Num.post)
		{
			numstr = (char *) palloc(numstr_pre_len + Num.post + 2);
			strcpy(numstr, orgnum);
			*(numstr + numstr_pre_len) = '.';
			memset(numstr + numstr_pre_len + 1, '0', Num.post);
			*(numstr + numstr_pre_len + Num.post + 1) = '\0';
		}
		else
			numstr = orgnum;


		if (numstr_pre_len < Num.pre)
			out_pre_spaces = Num.pre - numstr_pre_len;

		else if (numstr_pre_len > Num.pre)
		{
			numstr = (char *) palloc(Num.pre + Num.post + 2);
			fill_str(numstr, '#', Num.pre + Num.post + 1);
			*(numstr + Num.pre) = '.';
		}
	}

	NUM_TOCHAR_finish;
	PG_RETURN_TEXT_P(result);
}
