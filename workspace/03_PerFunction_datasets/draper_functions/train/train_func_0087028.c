get_first_col_type(Plan *plan, Oid *coltype, int32 *coltypmod)
{

	if (plan->targetlist)
	{
		TargetEntry *tent = (TargetEntry *) linitial(plan->targetlist);

		Assert(IsA(tent, TargetEntry));
		if (!tent->resjunk)
		{
			*coltype = exprType((Node *) tent->expr);
			*coltypmod = exprTypmod((Node *) tent->expr);
			return;
		}
	}
	*coltype = VOIDOID;
	*coltypmod = -1;
}
