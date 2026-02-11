unformat_request(struct mrpc_message *msg, void **result)
{
	xdrproc_t type;
	unsigned size;
	mrpc_status_t ret;

	if (msg->recv_error)
		return msg->recv_error;
	if (msg->conn->set->protocol->receiver_request_info(msg->hdr.cmd,
				&type, &size))
		return MINIRPC_ENCODING_ERR;
	ret=unformat_message(type, size, msg, result);
	if (ret)
		queue_ioerr_event(msg->conn, "Request payload deserialize "
					"failure, seq %u", msg->hdr.sequence);
	return ret;
}
