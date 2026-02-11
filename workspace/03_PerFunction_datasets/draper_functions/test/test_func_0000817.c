_route_msg_task_to_client(eio_obj_t *obj)
{
	struct task_read_info *out = (struct task_read_info *)obj->arg;
	struct client_io_info *client;
	struct io_buf *msg = NULL;
	eio_obj_t *eio;
	ListIterator clients;


	while (cbuf_used(out->buf) > 0
	       && _outgoing_buf_free(out->job)) {
		debug5("cbuf_used = %d", cbuf_used(out->buf));
		msg = _task_build_message(out, out->job, out->buf);
		if (msg == NULL)
			return;


		clients = list_iterator_create(out->job->clients);
		if (!clients)
			fatal("Could not allocate iterator");

		while((eio = list_next(clients))) {
			client = (struct client_io_info *)eio->arg;
			if (client->out_eof == true)
				continue;


			if (out->type==SLURM_IO_STDOUT) {
				if (client->ltaskid_stdout != -1 &&
				    client->ltaskid_stdout != out->ltaskid)
					continue;
			}
			if (out->type==SLURM_IO_STDERR) {
				if (client->ltaskid_stderr != -1 &&
				    client->ltaskid_stderr != out->ltaskid)
					continue;
			}

			debug5("======================== Enqueued message");
			xassert(client->magic == CLIENT_IO_MAGIC);
			if (list_enqueue(client->msg_queue, msg))
				msg->ref_count++;
		}
		list_iterator_destroy(clients);


		if (list_enqueue(out->job->outgoing_cache, msg)) {
			msg->ref_count++;
			_shrink_msg_cache(out->job->outgoing_cache, out->job);
		}
	}
}
