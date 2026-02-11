put_signal_args (Method *m)
{
	GList *li;
	GList *ali;
	int i;

	if (m->args->next == NULL)
		return;

	for (ali = m->gtktypes->next, li = m->args->next, i = 1;
	     li != NULL && ali != NULL;
	     li = li->next, ali = ali->next, i++) {
		FuncArg *fa = li->data;
		char *str = ali->data;
		char *cast = g_strdup (get_cast (str, FALSE));

		gboolean do_static =
			(strcmp  (str, "STRING") == 0 ||
			 strcmp  (str, "BOXED") == 0 ||
			 strncmp (str, "BOXED_", 6) == 0);
		char *set_func;
		char *t;

		if (cast == NULL) {
			cast = get_type (fa->atype, TRUE);
		}


		g_assert (cast != NULL);

		if (strncmp (str, "BOXED_", 6) == 0)
			t = g_strdup (&(str[6]));
		else
			t = g_strconcat ("G_TYPE_", str, NULL);

		out_printf (out,
			    "\t___param_values[%d].g_type = 0;\n"
			    "\tg_value_init (&___param_values[%d], %s);\n",
			    i, i, t);
		g_free (t);

		if (strcmp (str, "UNICHAR") == 0)

			set_func = g_strdup ("g_value_set_uint");
		else if (strncmp (str, "BOXED_", 6) == 0)
			set_func = g_strdup ("g_value_set_static_boxed");
		else
			set_func = g_strdup_printf ("g_value_set%s_%s",
						    do_static ? "_static" : "",
						    str);
		gob_strdown (set_func);

		out_printf (out, "\t%s (&___param_values[%d], (%s) %s);\n\n",
			    set_func, i, cast, fa->name);

		g_free (set_func);
		g_free (cast);
	}
}
