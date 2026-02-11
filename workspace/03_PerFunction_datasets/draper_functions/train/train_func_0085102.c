lookupcreatename(const char *name)
{
	unsigned  hashval = calchash(name);
	struct	macro	*hp, **hpp;

	for  (hpp = &hashtab[hashval]; (hp = *hpp);  hpp = &hp->next)
		if  (strcmp(name, hp->name) == 0)
			return  hp;
	if  (!(hp = (struct macro *) malloc(sizeof(struct macro))))
		nomem();
	hp->next = (struct macro *) 0;
	hp->name = stracpy(name);
	hp->expansion = (char *) 0;
	*hpp = hp;
	return  hp;
}
