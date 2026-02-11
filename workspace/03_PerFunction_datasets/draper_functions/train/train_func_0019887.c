nls_eval(nls_node **tree)
{
	nls_node *out;

	if (NLS_ISVAR(*tree)) {
		if (!(out = nls_symbol_get((*tree)->nn_var.nv_name))) {
			return 0;
		}
		nls_release(*tree);
		*tree = nls_grab(out);
		return 0;
	}
	if (!NLS_ISAPP(*tree)) {
		return 0;
	}
	return nls_apply(tree);
}
