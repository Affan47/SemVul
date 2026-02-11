xmms_ipc_register_signal (xmms_ipc_client_t *client,
                          xmms_ipc_msg_t *msg, xmmsv_t *arguments)
{
	xmmsv_t *arg;
	gint32 signalid;
	int r;

	if (!arguments || !xmmsv_list_get (arguments, 0, &arg)) {
		xmms_log_error ("No signalid in this msg?!");
		return;
	}

	r = xmmsv_get_int (arg, &signalid);

	if (!r) {
		xmms_log_error ("Cannot extract signal id from value");
		return;
	}

	if (signalid < 0 || signalid >= XMMS_IPC_SIGNAL_END) {
		xmms_log_error ("Bad signal id (%d)", signalid);
		return;
	}

	g_mutex_lock (client->lock);
	client->pendingsignals[signalid] = xmms_ipc_msg_get_cookie (msg);
	g_mutex_unlock (client->lock);
}
