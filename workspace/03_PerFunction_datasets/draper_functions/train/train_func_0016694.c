gkrellm_client_server_connect_state(void)
	{
	if (client_mode_thread_busy)
		return CONNECTING;
	if (_GK.client_mode && client_input_id > 0)
		return CONNECTED;
	else if (_GK.client_mode)
		return DISCONNECTED;
	else
		return NO_CLIENT;
	}
