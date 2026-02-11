gnm_expr_new_funcall1 (GnmFunc *func,
		       GnmExpr const *arg0)
{
	GnmExprConstPtr *argv = g_new (GnmExprConstPtr, 1);
	argv[0] = arg0;
	return gnm_expr_new_funcallv (func, 1, argv);
}
