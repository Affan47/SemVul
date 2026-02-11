collection_list_randomize(GList *list)
{
	guint random, length, i;
	gpointer tmp;
	GList *nlist, *olist;

	length = g_list_length(list);
	if (!length) return NULL;

	srand((unsigned int)time(NULL));

	for (i = 0; i < length; i++)
		{
		random = (guint) (1.0 * length * rand()/(RAND_MAX + 1.0));
		olist = g_list_nth(list, i);
		nlist = g_list_nth(list, random);
		tmp = olist->data;
		olist->data = nlist->data;
		nlist->data = tmp;
		}

	return list;
}
