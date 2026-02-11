isns_simple_transmit(isns_socket_t *sock, isns_simple_t *call,
			const isns_portal_info_t *dest,
			unsigned int timeout,
			isns_simple_callback_fn_t *user_callback)
{
	isns_message_t	*msg;
	int		status;

	isns_simple_print(call, isns_debug_message);

	status = isns_simple_encode(call, &msg);
	if (status != ISNS_SUCCESS) {
		isns_error("Unable to encode %s: %s\n",
				isns_function_name(call->is_function),
				isns_strerror(status));
		return status;
	}

	isns_debug_message("Sending message, len=%d\n",
			buf_avail(msg->im_payload));

	if (user_callback) {
		msg->im_callback = isns_simple_recv_response;
		msg->im_calldata = user_callback;
	}

	if (!isns_socket_submit(sock, msg, timeout))
		status = ISNS_INTERNAL_ERROR;
	isns_message_release(msg);
	return status;
}
