list_item_ids_start (const char *keyring, GnomeKeyringOperationGetListCallback callback,
                     gpointer data, GDestroyNotify destroy_data)
{
	DBusMessage *req;
	GkrOperation *op;
	gchar *path;

	g_return_val_if_fail (callback, NULL);

	path = gkr_encode_keyring_name (keyring);
	req = prepare_property_get (path, COLLECTION_INTERFACE, "Items");

	op = gkr_operation_new (callback, GKR_CALLBACK_RES_LIST, data, destroy_data);
	gkr_operation_push (op, list_item_ids_reply, GKR_CALLBACK_OP_MSG, NULL, NULL);
	gkr_operation_request (op, req);

	dbus_message_unref (req);
	g_free (path);

	return op;
}
