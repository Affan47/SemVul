sort_rules(GROUP *gp)
{
	RULE *rp, *rp1, *rptemp, *rpnext;
	UINT n;


	if(gp->nrules < 2) return;


	rptemp = (RULE *)checked_alloc(2*gp->nrules,sizeof(RULE));
	for(n=0,rp=gp->rules,rp1=rptemp; n<gp->nrules; n++,rp=rpnext,rp1++)
	{
		*rp1 = *rp; rpnext = rp->next; mem_free(rp);
	}


	qsort((void *)rptemp,(size_t)gp->nrules,sizeof(RULE),compare_rules);


	gp->rules = rptemp;
	for(n=0,rp=rptemp; n<gp->nrules; n++,rp++) rp->next = rp+1;
	rp->next = NULL;
}
