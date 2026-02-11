Note_numnotice(userrec *u)
{
	int	tot = 0;
	noterec	*n;

	for(n=u->notes; n!=NULL; n=n->next)
		if(n->flags & NOTE_NOTICE)
			tot++;

	return tot;
}
