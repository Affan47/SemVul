reset	    (pANTLR3_COMMON_TREE_NODE_STREAM ctns)
{
	if	(ctns->p != -1)
	{
		ctns->p									= 0;
	}
	ctns->tnstream->istream->lastMarker		= 0;


	if  (ctns->isRewriter != ANTLR3_TRUE)
    {
		if	(ctns->nodeStack != NULL)
		{
			ctns->nodeStack->free(ctns->nodeStack);
			ctns->nodeStack = antlr3StackNew(INITIAL_CALL_STACK_SIZE);
		}
	}
}
