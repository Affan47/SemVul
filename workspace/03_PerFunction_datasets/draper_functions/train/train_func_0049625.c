addRTEtoQuery(ParseState *pstate, RangeTblEntry *rte,
			  bool addToJoinList,
			  bool addToRelNameSpace, bool addToVarNameSpace)
{
	if (addToJoinList)
	{
		int			rtindex = RTERangeTablePosn(pstate, rte, NULL);
		RangeTblRef *rtr = makeNode(RangeTblRef);

		rtr->rtindex = rtindex;
		pstate->p_joinlist = lappend(pstate->p_joinlist, rtr);
	}
	if (addToRelNameSpace)
		pstate->p_relnamespace = lappend(pstate->p_relnamespace, rte);
	if (addToVarNameSpace)
		pstate->p_varnamespace = lappend(pstate->p_varnamespace, rte);
}
