symlook(char *sym, int space, void *install)
{
	long h;
	char *p;
	Symtab *s;

	for(p = sym, h = space; *p; h += *p++)
		h *= HASHMUL;
	if(h < 0)
		h = ~h;
	h %= NHASH;
	for(s = hash[h]; s; s = s->next)
		if((s->space == space) && (strcmp(s->name, sym) == 0))
			return(s);
	if(install == 0)
		return(0);
	s = (Symtab *)Malloc(sizeof(Symtab));
	s->space = space;
	s->name = sym;
	s->u.ptr = install;
	s->next = hash[h];
	hash[h] = s;
	return(s);
}
