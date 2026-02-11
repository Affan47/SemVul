_msg_thr_create(struct step_launch_state *sls, int num_nodes)
{
	int sock = -1;
	short port = -1;
	eio_obj_t *obj;
	int i, rc = SLURM_SUCCESS;
	pthread_attr_t attr;

	debug("Entering _msg_thr_create()");
	slurm_uid = (uid_t) slurm_get_slurm_user_id();

	sls->msg_handle = eio_handle_create();
	sls->num_resp_port = _estimate_nports(num_nodes, 48);
	sls->resp_port = xmalloc(sizeof(uint16_t) * sls->num_resp_port);


	if(!message_socket_ops.timeout)
		message_socket_ops.timeout = slurm_get_msg_timeout() * 8000;

	for (i = 0; i < sls->num_resp_port; i++) {
		if (net_stream_listen(&sock, &port) < 0) {
			error("unable to initialize step launch listening "
			      "socket: %m");
			return SLURM_ERROR;
		}
		sls->resp_port[i] = port;
		obj = eio_obj_create(sock, &message_socket_ops, (void *)sls);
		eio_new_initial_obj(sls->msg_handle, obj);
	}


	if (sls->slurmctld_socket_fd > -1) {
		obj = eio_obj_create(sls->slurmctld_socket_fd,
				     &message_socket_ops, (void *)sls);
		eio_new_initial_obj(sls->msg_handle, obj);
	}

	slurm_attr_init(&attr);
	if (pthread_create(&sls->msg_thread, &attr,
			   _msg_thr_internal, (void *)sls) != 0) {
		error("pthread_create of message thread: %m");

		sls->msg_thread = 0;
		rc = SLURM_ERROR;
	}
	slurm_attr_destroy(&attr);
	return rc;
}
