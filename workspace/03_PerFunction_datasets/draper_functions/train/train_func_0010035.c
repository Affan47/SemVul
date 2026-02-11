FcPopBinary (FcConfigParse *parse, FcOp op)
{
    FcExpr  *left, *expr = 0, *new;

    while ((left = FcPopExpr (parse)))
    {
	if (expr)
	{
	    new = FcExprCreateOp (parse->config, left, op, expr);
	    if (!new)
	    {
		FcConfigMessage (parse, FcSevereError, "out of memory");
		FcExprDestroy (left);
		FcExprDestroy (expr);
		return 0;
	    }
	    expr = new;
	}
	else
	    expr = left;
    }
    return expr;
}
