Response_deletemarkedmatches(resprec *r)
{
	machrec	*mr, *mr_next;
	int	tot = 0;

	mr = r->matches;
	while(mr != NULL)
	{
		mr_next = mr->next;
		if(mr->flags & MACHREC_DELETEME)
		{
			Response_deletematch(r,mr);
			tot++;
		}
		mr = mr_next;
	}

	return tot;
}
