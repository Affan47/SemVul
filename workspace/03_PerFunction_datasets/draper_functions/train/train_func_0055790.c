e_sexp_parse (ESExp *f)
{
	g_return_val_if_fail (IS_E_SEXP (f), -1);

	if (setjmp (f->failenv))
		return -1;

	if (f->tree)
		parse_term_free (f, f->tree);

	f->tree = parse_value (f);

	return 0;
}
