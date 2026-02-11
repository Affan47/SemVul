c_add_entry (VALUE self, VALUE arg)
{
	uint32_t id;

	PLAYLIST_METHOD_HANDLER_HEADER

	if (!NIL_P (rb_check_string_type (arg)))
		res = xmmsc_playlist_add_url (xmms->real, pl->name,
		                              StringValuePtr (arg));
	else {
		id = check_uint32 (arg);
		res = xmmsc_playlist_add_id (xmms->real, pl->name, id);
	}

	PLAYLIST_METHOD_HANDLER_FOOTER
}
