e_sexp_remove_symbol (ESExp *f,
                      gint scope,
                      const gchar *name)
{
	gint oldscope;
	struct _ESExpSymbol *s;

	g_return_if_fail (IS_E_SEXP (f));
	g_return_if_fail (name != NULL);

	oldscope = g_scanner_set_scope (f->scanner, scope);
	s = g_scanner_lookup_symbol (f->scanner, name);
	g_scanner_scope_remove_symbol (f->scanner, scope, name);
	g_scanner_set_scope (f->scanner, oldscope);
	if (s) {
		g_free (s->name);
		g_free (s);
	}
}
