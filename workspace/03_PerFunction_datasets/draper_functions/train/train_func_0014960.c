camel_sexp_parse (CamelSExp *sexp)
{
	g_return_val_if_fail (CAMEL_IS_SEXP (sexp), -1);

	if (setjmp (sexp->failenv)) {
		g_warning ("Error in parsing: %s", sexp->error);
		return -1;
	}

	if (sexp->tree)
		parse_term_free (sexp, sexp->tree);

	sexp->tree = parse_value (sexp);

	return 0;
}
