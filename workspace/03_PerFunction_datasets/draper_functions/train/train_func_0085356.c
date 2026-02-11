ExecInitBitmapOr(BitmapOr *node, EState *estate, int eflags)
{
	BitmapOrState *bitmaporstate = makeNode(BitmapOrState);
	PlanState **bitmapplanstates;
	int			nplans;
	int			i;
	ListCell   *l;
	Plan	   *initNode;


	Assert(!(eflags & (EXEC_FLAG_BACKWARD | EXEC_FLAG_MARK)));


	nplans = list_length(node->bitmapplans);

	bitmapplanstates = (PlanState **) palloc0(nplans * sizeof(PlanState *));


	bitmaporstate->ps.plan = (Plan *) node;
	bitmaporstate->ps.state = estate;
	bitmaporstate->bitmapplans = bitmapplanstates;
	bitmaporstate->nplans = nplans;


#define BITMAPOR_NSLOTS 0


	i = 0;
	foreach(l, node->bitmapplans)
	{
		initNode = (Plan *) lfirst(l);
		bitmapplanstates[i] = ExecInitNode(initNode, estate, eflags);
		i++;
	}

	return bitmaporstate;
}
