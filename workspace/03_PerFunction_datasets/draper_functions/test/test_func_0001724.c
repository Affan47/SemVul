camel_sexp_add_function (CamelSExp *sexp,
                         guint scope,
                         const gchar *name,
                         CamelSExpFunc func,
                         gpointer data)
{
	CamelSExpSymbol *sym;

	g_return_if_fail (CAMEL_IS_SEXP (sexp));
	g_return_if_fail (name != NULL);

	camel_sexp_remove_symbol (sexp, scope, name);

	sym = g_malloc0 (sizeof (*sym));
	sym->name = g_strdup (name);
	sym->f.func = func;
	sym->type = CAMEL_SEXP_TERM_FUNC;
	sym->data = data;

	g_scanner_scope_add_symbol (sexp->scanner, scope, sym->name, sym);
}
