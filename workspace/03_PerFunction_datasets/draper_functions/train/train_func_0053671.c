intersection_init_iterator(nodetrack_t* nt
,	gpointer	ghelp
,	const char*	node
,	cl_uuid_t	uuid)
{
	struct li_helper*	help = ghelp;
	gboolean		allfound = TRUE;
	int			j;

	for (j=1; allfound && j < help->i->ntables; ++j) {
		if (!nodetrack_ismember(help->i->tables[j]
		,	node, uuid)) {
			allfound = FALSE;
		}
	}
	if (allfound) {
		nodetrack_nodeup(help->i->intersection, node, uuid);
	}
}
