is_dev_in_dlist(const char *dev)
{
	int i;


	for (i = 0; i < G.devlist_i; i++)
		if (strcmp(G.dlist[i].dname, dev) == 0)

			return 1;


	return 0;
}
