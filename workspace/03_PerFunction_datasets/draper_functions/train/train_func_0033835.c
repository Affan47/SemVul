get_leftop(Expr *clause)
{
	OpExpr	   *expr = (OpExpr *) clause;

	if (expr->args != NIL)
		return linitial(expr->args);
	else
		return NULL;
}
