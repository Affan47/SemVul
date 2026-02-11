sacctmgr_find_cluster_from_list(
	List cluster_list, char *name)
{
	ListIterator itr = NULL;
	slurmdb_cluster_rec_t *cluster = NULL;

	if (!name || !cluster_list)
		return NULL;

	itr = list_iterator_create(cluster_list);
	while((cluster = list_next(itr))) {
		if (!strcasecmp(name, cluster->name))
			break;
	}
	list_iterator_destroy(itr);

	return cluster;
}
