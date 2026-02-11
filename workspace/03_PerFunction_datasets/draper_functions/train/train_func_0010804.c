lookup(char *s)
{
	int p;

	for (p = lastentry; p >= 0; p--)
		if (strcmp(symtable[p].lexptr, s) == 0)
			return &symtable[p];

	return NULL;
}
