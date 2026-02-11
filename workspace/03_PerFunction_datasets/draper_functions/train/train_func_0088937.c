select_p_ba_init(node_info_msg_t *node_info_ptr, bool sanity_check)
{
	int i, j, offset;
	int dims = slurmdb_setup_cluster_dims();

	if (select_cray_dim_size[0] == -1) {
		node_info_t *node_ptr;


		for (i = 1; i < dims; i++)
			select_cray_dim_size[i] = -1;
		for (i = 0; i < node_info_ptr->record_count; i++) {
			node_ptr = &(node_info_ptr->node_array[i]);
			if (!node_ptr->node_addr ||
			    (strlen(node_ptr->node_addr) != dims))
				continue;
			for (j = 0; j < dims; j++) {
				offset = select_char2coord(
					node_ptr->node_addr[j]);
				select_cray_dim_size[j] =
					MAX((offset+1),
					    select_cray_dim_size[j]);
			}
		}
	}


	if (working_cluster_rec) {
		xfree(working_cluster_rec->dim_size);
		working_cluster_rec->dim_size = xmalloc(sizeof(int) * dims);
		for (j = 0; j < dims; j++)
			working_cluster_rec->dim_size[j] =
				select_cray_dim_size[j];
	}

	other_ba_init(node_info_ptr, sanity_check);
}
