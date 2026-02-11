http_response_thread(thread_t * thread)
{
	checker_t *checker = THREAD_ARG(thread);
	http_checker_t *http_get_check = CHECKER_ARG(checker);
	http_t *http = HTTP_ARG(http_get_check);
	request_t *req = HTTP_REQ(http);
	unsigned timeout = checker->co->connection_to;


	if (thread->type == THREAD_READ_TIMEOUT)
		return timeout_epilog(thread, "=> CHECK failed on service"
				      " : recevice data <=\n\n", "WEB read");


	req->buffer = (char *) MALLOC(MAX_BUFFER_LENGTH);
	req->extracted = NULL;
	req->len = 0;
	req->error = 0;
	MD5_Init(&req->context);


	if (http_get_check->proto == PROTO_SSL)
		thread_add_read(thread->master, ssl_read_thread, checker,
				thread->u.fd, timeout);
	else
		thread_add_read(thread->master, http_read_thread, checker,
				thread->u.fd, timeout);
	return 0;
}
