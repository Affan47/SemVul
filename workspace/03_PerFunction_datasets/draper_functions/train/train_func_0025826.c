client_io_handler_create(slurm_step_io_fds_t fds,
			 int num_tasks,
			 int num_nodes,
			 slurm_cred_t *cred,
			 bool label)
{
	client_io_t *cio;
	int i;
	uint32_t siglen;
	char *sig;

	cio = (client_io_t *)xmalloc(sizeof(client_io_t));
	if (cio == NULL)
		return NULL;

	cio->num_tasks = num_tasks;
	cio->num_nodes = num_nodes;

	cio->label = label;
	if (cio->label)
		cio->label_width = _wid(cio->num_tasks);
	else
		cio->label_width = 0;

	if (slurm_cred_get_signature(cred, &sig, &siglen) < 0) {
		error("client_io_handler_create, invalid credential");
		return NULL;
	}
	cio->io_key = (char *)xmalloc(siglen);
	memcpy(cio->io_key, sig, siglen);


	cio->eio = eio_handle_create();


	cio->num_listen = _estimate_nports(num_nodes, 48);
	cio->listensock = (int *)xmalloc(cio->num_listen * sizeof(int));
	cio->listenport = (uint16_t *)xmalloc(cio->num_listen*sizeof(uint16_t));

	cio->ioserver = (eio_obj_t **)xmalloc(num_nodes*sizeof(eio_obj_t *));
	cio->ioservers_ready_bits = bit_alloc(num_nodes);
	cio->ioservers_ready = 0;
	pthread_mutex_init(&cio->ioservers_lock, NULL);

	_init_stdio_eio_objs(fds, cio);

	for (i = 0; i < cio->num_listen; i++) {
		eio_obj_t *obj;

		if (net_stream_listen(&cio->listensock[i],
				      (short *)&cio->listenport[i]) < 0) {
			fatal("unable to initialize stdio listen socket: %m");
		}
		debug("initialized stdio listening socket, port %d",
		      cio->listenport[i]);

		obj = _create_listensock_eio(cio->listensock[i], cio);
		eio_new_initial_obj(cio->eio, obj);
	}

	cio->free_incoming = list_create(NULL);
	cio->incoming_count = 0;
	for (i = 0; i < STDIO_MAX_FREE_BUF; i++) {
		list_enqueue(cio->free_incoming, _alloc_io_buf());
	}
	cio->free_outgoing = list_create(NULL);
	cio->outgoing_count = 0;
	for (i = 0; i < STDIO_MAX_FREE_BUF; i++) {
		list_enqueue(cio->free_outgoing, _alloc_io_buf());
	}
	cio->sls = NULL;

	return cio;
}
