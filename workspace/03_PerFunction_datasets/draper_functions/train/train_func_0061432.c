gdb_pass_through(char *cmd, FILE *fptr, ulong flags)
{
        struct gnu_request *req;
	int retval;

	if (CRASHDEBUG(1))
  		console("gdb_pass_through: [%s]\n", cmd);

        req = (struct gnu_request *)GETBUF(sizeof(struct gnu_request));
        req->buf = cmd;
	if (fptr)
		req->fp = fptr;
        req->command = GNU_PASS_THROUGH;
	req->flags = flags;

        gdb_interface(req);

	if ((req->flags & (GNU_RETURN_ON_ERROR|GNU_COMMAND_FAILED)) ==
	    (GNU_RETURN_ON_ERROR|GNU_COMMAND_FAILED))
		retval = FALSE;
	else
		retval = TRUE;

        FREEBUF(req);

	return retval;
}
