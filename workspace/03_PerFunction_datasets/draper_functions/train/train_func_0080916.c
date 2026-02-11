gkr_callback_invoke_ok_list (GkrCallback *cb, GList *value)
{
	g_assert (cb);
	g_assert (cb->type == GKR_CALLBACK_RES_LIST);
	g_assert (cb->callback);
	cb->type = 0;
	if (!cb->operation || gkr_operation_set_result (cb->operation, GNOME_KEYRING_RESULT_OK))
		((GnomeKeyringOperationGetListCallback)cb->callback) (GNOME_KEYRING_RESULT_OK, value, cb->user_data);
}
