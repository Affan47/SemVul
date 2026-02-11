lookupname(const char * name)
{
	unsigned  hashval = calchash(name);
	struct	macro	*hp;

	for  (hp = hashtab[hashval]; hp;  hp = hp->next)
		if  (strcmp(name, hp->name) == 0)
			return  hp;
	return  (struct macro *) 0;
}
