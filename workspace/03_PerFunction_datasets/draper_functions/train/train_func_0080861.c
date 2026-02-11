index_of_revision(revision_t *r)
{
	branch_t *b = r->branch;
	int i;
	for(i = 0; i < b->nrevs; i++)
	{
		if(r == b->revs[i])
			return i;
	}
	stack_msg(MSG_ERR, "index_of_revision: Cannot find revision in branch\n");
	return 0;
}
