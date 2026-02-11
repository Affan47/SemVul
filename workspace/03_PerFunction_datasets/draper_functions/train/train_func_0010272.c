wi_socket_read_to_string(wi_socket_t *socket, wi_time_interval_t timeout, wi_string_t *separator) {
	wi_string_t		*string, *substring;
	wi_uinteger_t	index;

	index = wi_string_index_of_string(socket->buffer, separator, 0);

	if(index != WI_NOT_FOUND) {
		substring = wi_string_substring_to_index(socket->buffer, index + wi_string_length(separator));

		wi_mutable_string_delete_characters_in_range(socket->buffer, wi_make_range(0, wi_string_length(substring)));

		return substring;
	}

	while((string = wi_socket_read_string(socket, timeout))) {
		if(wi_string_length(string) == 0)
			return string;

		wi_mutable_string_append_string(socket->buffer, string);

		index = wi_string_index_of_string(socket->buffer, separator, 0);

		if(index == WI_NOT_FOUND) {
			if(wi_string_length(socket->buffer) > _WI_SOCKET_BUFFER_MAX_SIZE) {
				wi_error_set_libwired_error_with_format(WI_ERROR_SOCKET_OVERFLOW, WI_STR("Buffer is %u bytes"), wi_string_length(socket->buffer));

				wi_mutable_string_set_string(socket->buffer, WI_STR(""));

				return NULL;
			}
		} else {
			substring = wi_string_substring_to_index(socket->buffer, index + wi_string_length(separator));

			wi_mutable_string_delete_characters_in_range(socket->buffer, wi_make_range(0, wi_string_length(substring)));

			return substring;
		}
	}

	return NULL;
}
