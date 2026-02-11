stub_dbus_connection_send_with_reply_and_block(value bus, value message,
                                                     value timeout)
{
	CAMLparam3(bus, message, timeout);
	CAMLlocal1(rmsg);
	DBusMessage *c_rmsg;
	DBusError error;

	dbus_error_init(&error);
	c_rmsg = dbus_connection_send_with_reply_and_block(
	                                               DBusConnection_val(bus),
	                                               DBusMessage_val(message),
	                                               Int_val (timeout),
	                                               &error);
	if (!c_rmsg)
		raise_dbus_error(&error);

	voidstar_alloc(rmsg, c_rmsg, finalize_dbus_message);
	CAMLreturn(rmsg);
}
