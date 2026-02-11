slurmdbd_unpack_cluster_cpus_msg(dbd_cluster_cpus_msg_t **msg,
				 uint16_t rpc_version, Buf buffer)
{
	dbd_cluster_cpus_msg_t *msg_ptr;
	uint32_t uint32_tmp;

	msg_ptr = xmalloc(sizeof(dbd_cluster_cpus_msg_t));
	*msg = msg_ptr;

	if (rpc_version >= SLURMDBD_2_3_VERSION) {
		safe_unpackstr_xmalloc(&msg_ptr->cluster_nodes,
				       &uint32_tmp, buffer);
		safe_unpack32(&msg_ptr->cpu_count, buffer);
		safe_unpack_time(&msg_ptr->event_time, buffer);
	}

	return SLURM_SUCCESS;

unpack_error:
	slurmdbd_free_cluster_cpus_msg(msg_ptr);
	*msg = NULL;
	return SLURM_ERROR;
}
