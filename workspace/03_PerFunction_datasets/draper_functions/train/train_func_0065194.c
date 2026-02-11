wi_socket_read_string(wi_socket_t *socket, wi_time_interval_t timeout) {
	wi_mutable_string_t		*string;
	char					buffer[WI_SOCKET_BUFFER_SIZE];
	int						bytes = -1;

	string = wi_autorelease(wi_string_init_with_capacity(wi_mutable_string_alloc(), WI_SOCKET_BUFFER_SIZE));
	bytes = _wi_socket_read_buffer(socket, timeout, buffer, WI_SOCKET_BUFFER_SIZE);

	if(bytes < 0)
		return NULL;

	wi_mutable_string_append_bytes(string, buffer, bytes);

	wi_runtime_make_immutable(string);

	return string;
}
