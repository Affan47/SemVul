addsrcfile(char *path)
{
	struct	listitem *p;
	int	i;


	if (nsrcfiles == msrcfiles) {
		msrcfiles += SRCINC;
		srcfiles = myrealloc(srcfiles, msrcfiles * sizeof(char *));
	}

	srcfiles[nsrcfiles++] = my_strdup(compath(path));
	p = mymalloc(sizeof(struct listitem));
	p->text = my_strdup(compath(path));
	i = hash(p->text) % HASHMOD;
	p->next = srcnames[i];
	srcnames[i] = p;
}
