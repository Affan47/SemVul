camel_sexp_finalize (GObject *object)
{
	CamelSExp *sexp = (CamelSExp *) object;

	if (sexp->tree) {
		parse_term_free (sexp, sexp->tree);
		sexp->tree = NULL;
	}

	camel_memchunk_destroy (sexp->term_chunks);
	camel_memchunk_destroy (sexp->result_chunks);

	g_scanner_scope_foreach_symbol (sexp->scanner, 0, free_symbol, NULL);
	g_scanner_destroy (sexp->scanner);


	G_OBJECT_CLASS (camel_sexp_parent_class)->finalize (object);
}
