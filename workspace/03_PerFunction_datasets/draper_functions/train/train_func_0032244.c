servlist_net_find (char *name, int *pos, int (*cmpfunc) (const char *, const char *))
{
	GSList *list = network_list;
	ircnet *net;
	int i = 0;

	while (list)
	{
		net = list->data;
		if (cmpfunc (net->name, name) == 0)
		{
			if (pos)
				*pos = i;
			return net;
		}
		i++;
		list = list->next;
	}

	return NULL;
}
