get_cluster_dims(node_info_msg_t *node_info_ptr)
{
	int *dim_size = slurmdb_setup_cluster_dim_size();

	if ((params.cluster_flags & CLUSTER_FLAG_CRAY) && dim_size) {
		static int cray_dim_size[3] = {-1, -1, -1};


		cray_dim_size[0] = dim_size[0];
		cray_dim_size[1] = dim_size[1];
		cray_dim_size[2] = dim_size[2];
		return cray_dim_size;
	}

	if (dim_size == NULL) {
		static int default_dim_size[1];
		default_dim_size[0] = node_info_ptr->record_count;
		return default_dim_size;
	}

	return dim_size;
}
