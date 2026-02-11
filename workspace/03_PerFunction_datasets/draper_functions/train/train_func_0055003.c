eval_eq (struct _CamelSExp *f,
         gint argc,
         struct _CamelSExpTerm **argv,
         gpointer data)
{
	struct _CamelSExpResult *r, *r1, *r2;

	r = camel_sexp_result_new (f, CAMEL_SEXP_RES_STRING);

	if (argc == 2) {
		GString *str = g_string_new ("( ");
		r1 = camel_sexp_term_eval (f, argv[0]);
		r2 = camel_sexp_term_eval (f, argv[1]);

		if (r1->type == CAMEL_SEXP_RES_INT)
			g_string_append_printf (str, "%d", r1->value.number);
		else if (r1->type == CAMEL_SEXP_RES_TIME)
			g_string_append_printf (str, "%" G_GINT64_FORMAT, (gint64) r1->value.time);
		else if (r1->type == CAMEL_SEXP_RES_STRING)
			g_string_append_printf (str, "%s", r1->value.string);

		if (!strstr (str->str, "completed-on") && !strstr (str->str, "follow-up")) {
			gboolean ut = FALSE;

			if (strstr (str->str, "usertags"))
				ut = TRUE;
			if (ut)
				g_string_append_printf (str, " LIKE ");
			else
				g_string_append_printf (str, " = ");
			if (r2->type == CAMEL_SEXP_RES_INT)
				g_string_append_printf (str, "%d", r2->value.number);
			if (r2->type == CAMEL_SEXP_RES_BOOL)
				g_string_append_printf (str, "%d", r2->value.boolean);
			else if (r2->type == CAMEL_SEXP_RES_TIME)
				g_string_append_printf (str, "%" G_GINT64_FORMAT, (gint64) r2->value.time);
			else if (r2->type == CAMEL_SEXP_RES_STRING) {
				gchar *tmp = g_strdup_printf ("%c%s%c", ut ? '%':' ', r2->value.string, ut ? '%':' ');
				gchar *safe = get_db_safe_string (tmp);
				g_string_append_printf (str, "%s", safe);
				g_free (safe);
				g_free (tmp);
			}
		}
		camel_sexp_result_free (f, r1);
		camel_sexp_result_free (f, r2);
		g_string_append (str, " )");
		r->value.string = str->str;
		g_string_free (str, FALSE);
	} else {
		r->value.string = g_strdup ("(0)");
	}
	return r;
}
