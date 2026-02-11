get_uncategorized_documented (void)
{
	GSList *funcs;
	GSList *li;
	GSList *list;

	funcs = d_getcontext();
	if (funcs == NULL)
		return NULL;

	list = NULL;

	for (li = funcs; li != NULL; li = li->next) {
		GelEFunc *f = li->data;
		GelHelp *help;
		if (f->id == NULL ||
		    f->id->token == NULL)
			continue;
		help = gel_get_help (f->id->token, FALSE );
		if (help != NULL &&
		    help->category == NULL &&
		    help->aliasfor == NULL)
			list = g_slist_insert_sorted (list,
						      help,
						      help_sort);
	}
	return list;
}
