format_reply_error(struct mrpc_message *request,
			mrpc_status_t status, struct mrpc_message **result)
{
	struct mrpc_message *msg;

	if (status == MINIRPC_OK)
		return MINIRPC_INVALID_ARGUMENT;
	if (format_message(request->conn, (xdrproc_t)xdr_void, NULL, &msg))
		return MINIRPC_ENCODING_ERR;
	msg->hdr.sequence=request->hdr.sequence;
	msg->hdr.status=status;
	msg->hdr.cmd=request->hdr.cmd;
	*result=msg;
	return MINIRPC_OK;
}
