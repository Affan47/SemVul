_forward_comm_set(struct kvs_comm_set *kvs_set_ptr)
{
	int i, rc = SLURM_SUCCESS;
	int tmp_host_cnt = kvs_set_ptr->host_cnt;
	slurm_msg_t msg_send;
	int msg_rc;

	kvs_set_ptr->host_cnt = 0;
	for (i=0; i<tmp_host_cnt; i++) {
		if (kvs_set_ptr->kvs_host_ptr[i].port == 0)
			continue;
		slurm_msg_t_init(&msg_send);
		msg_send.msg_type = PMI_KVS_GET_RESP;
		msg_send.data = (void *) kvs_set_ptr;
		slurm_set_addr(&msg_send.address,
			kvs_set_ptr->kvs_host_ptr[i].port,
			kvs_set_ptr->kvs_host_ptr[i].hostname);
		if (slurm_send_recv_rc_msg_only_one(&msg_send,
				&msg_rc, 0) < 0) {
			error("Could not forward msg to %s",
				kvs_set_ptr->kvs_host_ptr[i].hostname);
			msg_rc = 1;
		}
		rc = MAX(rc, msg_rc);
		xfree(kvs_set_ptr->kvs_host_ptr[i].hostname);
	}
	xfree(kvs_set_ptr->kvs_host_ptr);
	return rc;
}
