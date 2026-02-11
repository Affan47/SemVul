wait_for_free_request(struct TCP_Server_Info *server, const int timeout,
		      const int optype)
{
	int *val;

	val = server->ops->get_credits_field(server, optype);

	if (*val <= 0 && optype == CIFS_ECHO_OP)
		return -EAGAIN;
	return wait_for_free_credits(server, timeout, val);
}
