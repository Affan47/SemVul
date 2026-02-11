_unpack_kvs_data(struct kvs_comm_set **msg_ptr, Buf buffer,
			     uint16_t protocol_version)
{
	struct kvs_comm_set *msg;
	int i, j;

	msg = xmalloc(sizeof(struct kvs_comm_set));
	*msg_ptr = msg;

	safe_unpack16(&msg->host_cnt, buffer);
	msg->kvs_host_ptr = xmalloc(sizeof(struct kvs_hosts) *
				    msg->host_cnt);
	for (i=0; i<msg->host_cnt; i++) {
		if (_unpack_kvs_host_rec(&msg->kvs_host_ptr[i], buffer,
					 protocol_version))
			goto unpack_error;
	}

	safe_unpack16(&msg->kvs_comm_recs, buffer);
	msg->kvs_comm_ptr = xmalloc(sizeof(struct kvs_comm) *
				    msg->kvs_comm_recs);
	for (i=0; i<msg->kvs_comm_recs; i++) {
		if (_unpack_kvs_rec(&msg->kvs_comm_ptr[i], buffer,
				    protocol_version))
			goto unpack_error;
	}
	return SLURM_SUCCESS;

unpack_error:
	for (i=0; i<msg->host_cnt; i++)
		xfree(msg->kvs_host_ptr[i].hostname);
	xfree(msg->kvs_host_ptr);
	for (i=0; i<msg->kvs_comm_recs; i++) {
		xfree(msg->kvs_comm_ptr[i]->kvs_name);
		for (j=0; j<msg->kvs_comm_ptr[i]->kvs_cnt; j++) {
			xfree(msg->kvs_comm_ptr[i]->kvs_keys[j]);
			xfree(msg->kvs_comm_ptr[i]->kvs_values[j]);
		}
		xfree(msg->kvs_comm_ptr[i]->kvs_keys);
		xfree(msg->kvs_comm_ptr[i]->kvs_values);
	}
	xfree(msg->kvs_comm_ptr);
	xfree(msg);
	*msg_ptr = NULL;
	return SLURM_ERROR;
}
