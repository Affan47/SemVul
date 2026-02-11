timeof(char *name, int force)
{
	Symtab *sym;
	long t;

	if(utfrune(name, '('))
		return atimeof(force, name);

	if(force)
		return mtime(name);


	sym = symlook(name, S_TIME, 0);
	if (sym)
		return sym->u.value;

	t = mtime(name);
	if(t == 0)
		return 0;

	symlook(name, S_TIME, (void*)t);
	return t;
}
