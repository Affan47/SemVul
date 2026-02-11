handle_relay_auth_message(struct relay_server *rs, struct auth_message *am)
{
	am->resume_func(am->success, am->out_oauth, am->max_session_time, am->key, am->pwd,
				&(rs->server), am->ctxkey, &(am->in_buffer));
	if (am->in_buffer.nbh) {
		ioa_network_buffer_delete(rs->ioa_eng, am->in_buffer.nbh);
		am->in_buffer.nbh = NULL;
	}
}
