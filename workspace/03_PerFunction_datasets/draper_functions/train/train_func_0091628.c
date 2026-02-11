xmmsc_ipc_msg_write (xmmsc_ipc_t *ipc, xmms_ipc_msg_t *msg, uint32_t cookie)
{
	x_return_val_if_fail (ipc, false);

	xmms_ipc_msg_set_cookie (msg, cookie);
	x_queue_push_tail (ipc->out_msg, msg);

	if (ipc->need_out_callback) {
		ipc->need_out_callback (1, ipc->need_out_data);
	}

	return true;
}
