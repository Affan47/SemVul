good_nodes_from_inx(List local_cluster_list,
			       void **object, char *node_inx,
			       int submit)
{
	local_cluster_t **curr_cluster = (local_cluster_t **)object;


	if (*curr_cluster) {
		bitstr_t *job_bitmap = NULL;
		if (!node_inx || !node_inx[0])
			return 0;
		if ((submit < (*curr_cluster)->start)
		    || (submit > (*curr_cluster)->end)) {
			local_cluster_t *local_cluster = NULL;

			ListIterator itr =
				list_iterator_create(local_cluster_list);
			while ((local_cluster = list_next(itr))) {
				if ((submit >= local_cluster->start)
				    && (submit <= local_cluster->end)) {
					*curr_cluster = local_cluster;
					break;
				}
			}
			list_iterator_destroy(itr);
			if (!local_cluster)
				return 0;
		}
		job_bitmap = bit_alloc(hostlist_count((*curr_cluster)->hl));
		bit_unfmt(job_bitmap, node_inx);
		if (!bit_overlap((*curr_cluster)->asked_bitmap, job_bitmap)) {
			FREE_NULL_BITMAP(job_bitmap);
			return 0;
		}
		FREE_NULL_BITMAP(job_bitmap);
	}
	return 1;
}
