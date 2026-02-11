Xds(int modifier, char *label, char *mnemo, char *oper)
{
	struct result *r;
	register int i,init;
	char *s1,*s2;

	if (filter(oper,"?_,_?",&s1,&s2) )
	{	oper=s1;
		r=parse(s2);
		checktype(r,L_ABSOLUTE);
		init=r->value;
		if (init & 0xffffff00)
			warning("multiple byte initialiser");
	}
	else
		init=0;

	r=parse(oper);
	checktype(r,L_ABSOLUTE);
	i=r->value;
	while ( i-- )
		insert8(init);
	advance=r->value;
        return 0;
}
