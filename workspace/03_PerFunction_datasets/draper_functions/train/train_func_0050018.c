duplalias(alias)
shaliastable *alias;
{
	shaliastable *dupl;
	int i, n;

	if (!alias) n = 0;
	else for (n = 0; alias[n].ident; n++) ;
	dupl = (shaliastable *)Xmalloc((n + 1) * sizeof(shaliastable));
	for (i = 0; i < n; i++) {
		dupl[i].ident = Xstrdup(alias[i].ident);
		dupl[i].comm = Xstrdup(alias[i].comm);
	}
	dupl[i].ident = NULL;

	return(dupl);
}
