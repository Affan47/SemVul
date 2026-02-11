gnome_keyring_get_default_keyring (GnomeKeyringOperationGetStringCallback  callback,
                                   gpointer                                data,
                                   GDestroyNotify                          destroy_data)
{
	GkrOperation *op;

	gkr_init ();

	op = get_default_keyring_start (callback, data, destroy_data);
	return gkr_operation_pending_and_unref (op);
}
