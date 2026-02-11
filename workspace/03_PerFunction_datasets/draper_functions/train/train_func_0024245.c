gnumeric_n (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	GnmValue *v;

	if (VALUE_IS_NUMBER (argv[0]))
		return value_new_float (value_get_as_float (argv[0]));

	if (!VALUE_IS_STRING (argv[0]))
		return value_new_error_NUM (ei->pos);

	v = format_match_number (value_peek_string (argv[0]),
				 NULL,
				 workbook_date_conv (ei->pos->sheet->workbook));
	if (v != NULL)
		return v;

	return value_new_float (0);
}
