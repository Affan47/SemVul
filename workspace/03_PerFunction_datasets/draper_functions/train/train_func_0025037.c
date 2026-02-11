rb_connect_callback(rb_fde_t *F, int status)
{
	CNCB *hdl;
	void *data;
	int errtmp = errno;


	if(F == NULL || F->connect == NULL || F->connect->callback == NULL)
		return;

	hdl = F->connect->callback;
	data = F->connect->data;
	F->connect->callback = NULL;


	rb_settimeout(F, 0, NULL, NULL);
	errno = errtmp;

	hdl(F, status, data);
}
