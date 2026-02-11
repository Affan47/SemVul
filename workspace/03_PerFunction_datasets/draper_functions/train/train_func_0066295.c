term_eval_caststring (struct _ESExp *f,
                      gint argc,
                      struct _ESExpResult **argv,
                      gpointer data)
{
	struct _ESExpResult *r;

	if (argc != 1)
		e_sexp_fatal_error (f, "Incorrect argument count to (cast-string )");

	r = e_sexp_result_new (f, ESEXP_RES_STRING);
	switch (argv[0]->type) {
	case ESEXP_RES_INT:
		r->value.string = g_strdup_printf ("%d", argv[0]->value.number);
		break;
	case ESEXP_RES_BOOL:
		r->value.string = g_strdup_printf ("%d", argv[0]->value.boolean != 0);
		break;
	case ESEXP_RES_STRING:
		r->value.string = g_strdup (argv[0]->value.string);
		break;
	default:
		e_sexp_result_free (f, r);
		e_sexp_fatal_error (f, "Invalid type in (gint )");
	}

	return r;
}
