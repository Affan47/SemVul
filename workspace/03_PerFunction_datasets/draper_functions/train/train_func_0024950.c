make_expr_example (Sheet *sheet, const char *text, gboolean localized)
{
	GnmLocale *oldlocale = NULL;
	GnmExprTop const *texpr;
	char *res;
	GnmParsePos pp;
	GnmEvalPos ep;
	GnmConventions const *convs = gnm_conventions_default;

	eval_pos_init_sheet (&ep, sheet);
	parse_pos_init_evalpos (&pp, &ep);

	if (!localized)
		oldlocale = gnm_push_C_locale ();
	texpr = gnm_expr_parse_str (text, &pp,
				    GNM_EXPR_PARSE_DEFAULT,
				    convs,
				    NULL);
	if (!localized)
		gnm_pop_C_locale (oldlocale);

	if (texpr) {
		char *etxt = gnm_expr_top_as_string (texpr, &pp, convs);
		GnmValue *val = gnm_expr_top_eval
			(texpr, &ep, GNM_EXPR_EVAL_PERMIT_NON_SCALAR);
		GOFormat const *format = auto_style_format_suggest (texpr, &ep);
		char *vtxt = format_value (format, val, -1,
					   workbook_date_conv
					   (sheet->workbook));

		go_format_unref (format);
		gnm_expr_top_unref (texpr);
		value_release (val);

		res = g_strdup_printf (_("%s evaluates to %s."), etxt, vtxt);

		g_free (etxt);
		g_free (vtxt);
	} else {
		g_warning ("Failed to parse [%s]", text);
		res = g_strdup ("");
	}

	return res;
}
