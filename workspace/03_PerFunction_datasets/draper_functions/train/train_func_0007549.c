data_book_handle_close_cb (EDBusAddressBook *interface,
                           GDBusMethodInvocation *invocation,
                           EDataBook *data_book)
{
	EBookBackend *backend;
	const gchar *sender;


	e_dbus_address_book_complete_close (interface, invocation);

	backend = e_data_book_ref_backend (data_book);
	g_return_val_if_fail (backend != NULL, FALSE);

	sender = g_dbus_method_invocation_get_sender (invocation);
	g_signal_emit_by_name (backend, "closed", sender);

	g_object_unref (backend);

	return TRUE;
}
