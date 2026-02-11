rail_core_handle_exec_result(
	RAIL_SESSION* session,
	uint16 flags,
	uint16 exec_result,
	uint32 raw_result,
	RAIL_UNICODE_STRING * exe_or_file
	)
{
	RAIL_VCHANNEL_EVENT event = {0};
	RAIL_STRING exe_or_file_;

	DEBUG_RAIL("rail_core_handle_exec_result: session=0x%p flags=0x%X "
		"exec_result=0x%X raw_result=0x%X exe_or_file=(length=%d dump>)",
		session, flags, exec_result, raw_result, exe_or_file->length);

#ifdef WITH_DEBUG_RAIL
	freerdp_hexdump(exe_or_file->buffer, exe_or_file->length);
#endif

	rail_unicode_string2string(session, exe_or_file, &exe_or_file_);

	init_vchannel_event(&event, RAIL_VCHANNEL_EVENT_EXEC_RESULT_RETURNED);
	event.param.exec_result_info.flags = flags;
	event.param.exec_result_info.exec_result = exec_result;
	event.param.exec_result_info.raw_result = raw_result;
	event.param.exec_result_info.exe_or_file = exe_or_file_.buffer;


	session->event_sender->send_rail_vchannel_event(
		session->event_sender->event_sender_object,
		&event);
}
