build_job_resources(job_resources_t *job_resrcs,
			       void *node_rec_table, uint16_t fast_schedule)
{
	int i, bitmap_len;
	int core_cnt = 0, sock_inx = -1;
	uint32_t cores, socks;
	struct node_record *node_ptr, *node_record_table;

	if (job_resrcs->node_bitmap == NULL) {
		error("build_job_resources: node_bitmap is NULL");
		return SLURM_ERROR;
	}

	node_record_table = (struct node_record *) node_rec_table;
	xfree(job_resrcs->sockets_per_node);
	xfree(job_resrcs->cores_per_socket);
	xfree(job_resrcs->sock_core_rep_count);
	job_resrcs->sockets_per_node = xmalloc(sizeof(uint16_t) *
					       job_resrcs->nhosts);
	job_resrcs->cores_per_socket = xmalloc(sizeof(uint16_t) *
					       job_resrcs->nhosts);
	job_resrcs->sock_core_rep_count = xmalloc(sizeof(uint32_t) *
						  job_resrcs->nhosts);

	bitmap_len = bit_size(job_resrcs->node_bitmap);
	for (i=0; i<bitmap_len; i++) {
		if (!bit_test(job_resrcs->node_bitmap, i))
			continue;
		node_ptr = node_record_table + i;
		if (fast_schedule) {
			socks = node_ptr->config_ptr->sockets;
			cores = node_ptr->config_ptr->cores;
		} else {
			socks = node_ptr->sockets;
			cores = node_ptr->cores;
		}
		if ((sock_inx < 0) ||
		    (socks != job_resrcs->sockets_per_node[sock_inx]) ||
		    (cores != job_resrcs->cores_per_socket[sock_inx])) {
			sock_inx++;
			job_resrcs->sockets_per_node[sock_inx] = socks;
			job_resrcs->cores_per_socket[sock_inx] = cores;
		}
		job_resrcs->sock_core_rep_count[sock_inx]++;
		core_cnt += (cores * socks);
	}
#ifndef HAVE_BG
	job_resrcs->core_bitmap      = bit_alloc(core_cnt);
	job_resrcs->core_bitmap_used = bit_alloc(core_cnt);
#endif
	return SLURM_SUCCESS;
}
