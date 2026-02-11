alloc_module(char *name, char *subdir)
{
	unsigned  mhash = mhashcalc(name);
	struct	module	*mp;
	struct	module_list	*result = alloc_modlist();

	for  (mp = modhashtab[mhash]; mp; mp = mp->mod_next)
		if  (strcmp(mp->mod_name, name) == 0)  {
			result->ml_mod = mp;
			if  (!mp->mod_subdir)
				mp->mod_subdir = subdir;
			return  result;
		}

	mp = (struct module *) malloc(sizeof(struct module));
	if  (!mp)
		nomem();
	mp->mod_next = modhashtab[mhash];
	modhashtab[mhash] = mp;
	mp->mod_name = name;
	mp->mod_subdir = subdir;
	mp->mod_pl = (struct program_list *) 0;
	mp->mod_scanned = 0;
	result->ml_mod = mp;
	return  result;
}
