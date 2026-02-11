copy_job_resources_node(job_resources_t *job_resrcs_ptr,
					  uint32_t node_id)
{
	int i, bit_inx = 0, core_cnt = 0;
	bitstr_t *core_bitmap;

	xassert(job_resrcs_ptr);

	for (i = 0; i < job_resrcs_ptr->nhosts; i++) {
		if (job_resrcs_ptr->sock_core_rep_count[i] <= node_id) {
			bit_inx += job_resrcs_ptr->sockets_per_node[i] *
				   job_resrcs_ptr->cores_per_socket[i] *
				   job_resrcs_ptr->sock_core_rep_count[i];
			node_id -= job_resrcs_ptr->sock_core_rep_count[i];
		} else {
			bit_inx += job_resrcs_ptr->sockets_per_node[i] *
				   job_resrcs_ptr->cores_per_socket[i] *
				   node_id;
			core_cnt = job_resrcs_ptr->sockets_per_node[i] *
				   job_resrcs_ptr->cores_per_socket[i];
			break;
		}
	}
	if (core_cnt < 1) {
		error("copy_job_resources_node: core_cnt=0");
		return NULL;
	}

	i = bit_size(job_resrcs_ptr->core_bitmap);
	if ((bit_inx + core_cnt) > i) {
		error("copy_job_resources_node: offset > bitmap size "
		      "(%d >= %d)", (bit_inx + core_cnt), i);
		return NULL;
	}

	core_bitmap = bit_alloc(core_cnt);
	if (!core_bitmap)
		fatal("copy_job_resources_node: bit_alloc(%d): %m", core_cnt);
	for (i = 0; i < core_cnt; i++) {
		if (bit_test(job_resrcs_ptr->core_bitmap, bit_inx++))
			bit_set(core_bitmap, i);
	}

	return core_bitmap;
}
