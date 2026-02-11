get_simple_binary_op_name(OpExpr *expr)
{
	List	   *args = expr->args;

	if (list_length(args) == 2)
	{

		Node	   *arg1 = (Node *) linitial(args);
		Node	   *arg2 = (Node *) lsecond(args);
		const char *op;

		op = generate_operator_name(expr->opno, exprType(arg1), exprType(arg2));
		if (strlen(op) == 1)
			return op;
	}
	return NULL;
}
