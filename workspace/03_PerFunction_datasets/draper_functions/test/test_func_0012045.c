gnumeric_numbervalue (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	char const *sep = value_peek_string (argv[1]);
	if (strlen(sep) != 1 || (*sep != '.' && *sep != ',')) {
		return value_new_error_VALUE (ei->pos);
	}

	if (VALUE_IS_EMPTY (argv[0]) || VALUE_IS_NUMBER (argv[0]))
		return value_dup (argv[0]);
	else {
		GnmValue *v;
		char const *p = value_peek_string (argv[0]);
		GString *curr;
		GString *thousand;
		GString *decimal;
		GOFormatFamily family = GO_FORMAT_GENERAL;

		decimal = g_string_new (sep);
		thousand = g_string_new ((*sep == '.') ? ",":".");
		curr = g_string_new ("$");


		while (*p && g_unichar_isspace (g_utf8_get_char (p)))
		       p = g_utf8_next_char (p);

		v = format_match_decimal_number_with_locale
			(p, &family, curr, thousand, decimal);

		g_string_free (decimal, TRUE);
		g_string_free (thousand, TRUE);
		g_string_free (curr, TRUE);

		if (v == NULL)
			v = format_match_number
				(p, NULL,
				 workbook_date_conv (ei->pos->sheet->workbook));

		if (v != NULL)
			return v;
		return value_new_error_VALUE (ei->pos);
	}
}
