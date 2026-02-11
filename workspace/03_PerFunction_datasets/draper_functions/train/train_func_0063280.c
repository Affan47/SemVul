rail_vchannel_send_exec_order(
		RAIL_SESSION * session,
		uint16 flags,
		RAIL_UNICODE_STRING* exe_or_file,
		RAIL_UNICODE_STRING* working_directory,
		RAIL_UNICODE_STRING* arguments
		)
{
	STREAM st_stream = {0};
	STREAM* s = &st_stream;

	uint16 exe_or_file_length        = exe_or_file->length;
	uint16 working_directory_length  = working_directory->length;
	uint16 arguments_length          = arguments->length;

	size_t data_length =
		2 +
		2 +
		2 +
		2 +
		exe_or_file_length +
		working_directory_length +
		arguments_length;

	void*  data = rail_alloc_order_data(data_length);

	stream_init_by_allocated_data(s, data, data_length);

	stream_write_uint16(s, flags);
	stream_write_uint16(s, exe_or_file_length);
	stream_write_uint16(s, working_directory_length);
	stream_write_uint16(s, arguments_length);

	write_rail_unicode_string_content(s, exe_or_file);
	write_rail_unicode_string_content(s, working_directory);
	write_rail_unicode_string_content(s, arguments);

	rail_vchannel_send_order_data(session, RDP_RAIL_ORDER_EXEC, data,
			data_length);
}
