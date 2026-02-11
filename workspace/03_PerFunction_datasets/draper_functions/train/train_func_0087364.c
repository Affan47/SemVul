http_response_thread(thread_t * thread)
{
	SOCK *sock_obj = THREAD_ARG(thread);


	if (thread->type == THREAD_READ_TIMEOUT)
		return epilog(thread);


	sock_obj->buffer = (char *) MALLOC(MAX_BUFFER_LENGTH);


	sock_obj->hash = &hashes[req->hash];
	HASH_INIT(sock_obj);


	if (req->ssl)
		thread_add_read(thread->master, ssl_read_thread, sock_obj,
				thread->u.fd, HTTP_CNX_TIMEOUT);
	else
		thread_add_read(thread->master, http_read_thread, sock_obj,
				thread->u.fd, HTTP_CNX_TIMEOUT);
	return 0;
}
