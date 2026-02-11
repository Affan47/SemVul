check_header (struct _CamelSExp *f,
              gint argc,
              struct _CamelSExpResult **argv,
              gpointer data,
              camel_search_match_t how)
{
	CamelSExpResult *r;
	gchar *str = NULL;

	d (printf ("executing check-header %d\n", how));


	if (argc > 1 && argv[0]->type == CAMEL_SEXP_RES_STRING) {
		gchar *headername;
		gint i;


		headername = camel_db_get_column_name (argv[0]->value.string);
		if (!headername) {
			gboolean *pcontains_unknown_column = (gboolean *) data;
			*pcontains_unknown_column = TRUE;

			headername = g_strdup ("unknown");
		}


		for (i = 1; i < argc; i++) {
			if (argv[i]->type == CAMEL_SEXP_RES_STRING) {
				gchar *value = NULL, *tstr = NULL;
				if (argv[i]->value.string[0] == 0)
					continue;
				if (how == CAMEL_SEARCH_MATCH_CONTAINS || how == CAMEL_SEARCH_MATCH_WORD) {
					tstr = g_strdup_printf ("%c%s%c", '%', argv[i]->value.string, '%');
					value = get_db_safe_string (tstr);
					g_free (tstr);
				} else if (how == CAMEL_SEARCH_MATCH_ENDS) {
					tstr = g_strdup_printf ("%c%s", '%', argv[i]->value.string);
					value = get_db_safe_string (tstr);
					g_free (tstr);
				} else if (how == CAMEL_SEARCH_MATCH_STARTS) {
					tstr = g_strdup_printf ("%s%c", argv[i]->value.string, '%');
					value = get_db_safe_string (tstr);
					g_free (tstr);
				} else if (how == CAMEL_SEARCH_MATCH_EXACT) {
					tstr = g_strdup_printf ("%c%s%c", '%', argv[i]->value.string, '%');
					value = get_db_safe_string (tstr);
					g_free (tstr);
				}
				str = g_strdup_printf ("(%s IS NOT NULL AND %s LIKE %s)", headername, headername, value);
				g_free (value);
			}
		}
		g_free (headername);
	}


	r = camel_sexp_result_new (f, CAMEL_SEXP_RES_STRING);
	r->value.string = str;

	return r;
}
