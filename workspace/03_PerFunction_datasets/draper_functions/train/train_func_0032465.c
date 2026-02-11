get_keyring_info_reply (GkrOperation *op, DBusMessage *reply, gpointer user_data)
{
	GnomeKeyringResult res;
	GnomeKeyringInfo *info;
	GkrCallback *cb;

	if (gkr_operation_handle_errors (op, reply))
		return;

	info = g_new0 (GnomeKeyringInfo, 1);
	res = decode_property_dict (reply, get_keyring_info_foreach, info);
	if (res == GNOME_KEYRING_RESULT_OK) {
		cb = gkr_operation_pop (op);
		gkr_callback_invoke_ok_keyring_info (cb, info);
		if (cb->callback == get_keyring_info_sync)
			info = NULL;
	} else {
		gkr_operation_complete (op, res);
	}

	gnome_keyring_info_free (info);
}
