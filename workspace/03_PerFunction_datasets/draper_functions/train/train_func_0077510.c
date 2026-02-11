hdhomerun_debug_output_message_sock(struct hdhomerun_debug_t *dbg, struct hdhomerun_debug_message_t *message)
{
	if (dbg->sock == HDHOMERUN_SOCK_INVALID) {
		uint64_t current_time = getcurrenttime();
		if (current_time < dbg->connect_delay) {
			return FALSE;
		}
		dbg->connect_delay = current_time + HDHOMERUN_DEBUG_CONNECT_RETRY_TIME;

		dbg->sock = hdhomerun_sock_create_tcp();
		if (dbg->sock == HDHOMERUN_SOCK_INVALID) {
			return FALSE;
		}

		uint32_t remote_addr = hdhomerun_sock_getaddrinfo_addr(dbg->sock, HDHOMERUN_DEBUG_HOST);
		if (remote_addr == 0) {
			hdhomerun_debug_close_internal(dbg);
			return FALSE;
		}

		if (!hdhomerun_sock_connect(dbg->sock, remote_addr, HDHOMERUN_DEBUG_PORT, HDHOMERUN_DEBUG_CONNECT_TIMEOUT)) {
			hdhomerun_debug_close_internal(dbg);
			return FALSE;
		}
	}

	size_t length = strlen(message->buffer);
	if (!hdhomerun_sock_send(dbg->sock, message->buffer, length, HDHOMERUN_DEBUG_SEND_TIMEOUT)) {
		hdhomerun_debug_close_internal(dbg);
		return FALSE;
	}

	return TRUE;
}
