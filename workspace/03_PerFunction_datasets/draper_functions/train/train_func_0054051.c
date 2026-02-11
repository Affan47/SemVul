_in_slurm_partition(List slurm_nodes, List bg_nodes)
{
	ListIterator slurm_itr;
	ListIterator bg_itr;
	int *coord = NULL;
	int *slurm_coord = NULL;
	int found = 0, i;

	bg_itr = list_iterator_create(bg_nodes);
	slurm_itr = list_iterator_create(slurm_nodes);
	while ((coord = list_next(bg_itr)) != NULL) {
		list_iterator_reset(slurm_itr);
		found = 0;
		while ((slurm_coord = list_next(slurm_itr)) != NULL) {
			for (i = 0; i < params.cluster_dims; i++) {
				if (coord[i] != slurm_coord[i])
					break;
			}
			if (i >= params.cluster_dims) {
				found = 1;
				break;
			}
		}
		if (!found)
			break;
	}
	list_iterator_destroy(slurm_itr);
	list_iterator_destroy(bg_itr);

	if (found)
		return 1;
	else
		return 0;

}
