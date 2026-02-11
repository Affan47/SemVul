CsfGetAttrBlock(
	MAP *m,
	CSF_ATTR_ID id,
	ATTR_CNTRL_BLOCK *b)


{
	CSF_FADDR next;

	next = m->main.attrTable;
	while (next != 0 )
	{
		CsfReadAttrBlock(m, next, b);
		if (CsfGetAttrIndex(id, b) != NR_ATTR_IN_BLOCK)
			break;
		next = b->next;
	}
	return(next);
}
