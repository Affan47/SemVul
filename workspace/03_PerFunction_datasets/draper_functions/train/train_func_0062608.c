DumpRemainingTokSets(void)
#else
DumpRemainingTokSets()
#endif
{
	TCnode *p;
	ListNode *t;


	if ( tclasses==NULL ) return;
	for (t = tclasses->next; t!=NULL; t=t->next)
	{
		unsigned e;
		p = (TCnode *) t->elem;
		if ( p->dumped ) continue;
		e = DefErrSet(&(p->tset), 0, TokenString(p->tok));
		p->dumped = 1;
		p->setnum = e;
	}
}
