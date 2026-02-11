setcap(
	char *name,
	struct cmdtable *table,
	char *string
	)
{
	int i;

	for (i = 0; table[i].name[0] != '\0'; i++) {
		if (strcasecmp(name, table[i].name) == 0) {
			strcpy(table[i].descr, string);
			return;
		}
	}
	strcpy(table[i].name, name);
	strcpy(table[i].descr, string);
	table[i + 1].name[0]  = '\0';
	table[i + 1].ident = R_ERR;
	table[i + 1].descr[0] = '\0';
}
