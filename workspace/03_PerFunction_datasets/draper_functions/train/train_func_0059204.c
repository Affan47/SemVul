function_uni_op (GelCtx *ctx, GelETree *n, GelETree *l)
{
	int i;
	GSList *args;
	GelETree *la;
	GelETree *nn;
	GelEFunc *f, *a;

	a = get_func_from (l, FALSE );
	if (a == NULL) {
		return TRUE;
	}

	if G_UNLIKELY (a->vararg) {
		gel_errorout (_("Operations on functions with variable argument list not supported"));
		return TRUE;
	}

	la = make_funccall (a);

	GEL_GET_NEW_NODE (nn);
	nn->type = GEL_OPERATOR_NODE;
	nn->op.oper = n->op.oper;
	nn->op.args = la;
	nn->op.args->any.next = NULL;
	nn->op.nargs = 1;

	args = NULL;
	for (i = a->nargs -1; i >= 0; i--) {
		args = g_slist_prepend (args, get_fake_token (i));
	}

	f = d_makeufunc (NULL ,
			 nn ,
			 args, a->nargs,
			 NULL );
	freetree_full (n, TRUE , FALSE );
	n->type = GEL_FUNCTION_NODE;
	n->func.func = f;
	n->func.func->context = -1;

	n->func.func->never_on_subst_list = 1;

	return TRUE;
}
