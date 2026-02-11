stub_dbus_message_new_error(value reply_to, value error_name,
                                  value error_message)
{
	CAMLparam3(reply_to, error_name, error_message);
	CAMLlocal1(msg);
	DBusMessage *c_msg;
	char *errname;

	errname = __error_table[Int_val(error_name)];
	c_msg = dbus_message_new_error(DBusMessage_val(reply_to),
	                               errname,
	                               String_val(error_message));
	if (!c_msg)
		raise_dbus_internal_error("message_new_error");
	voidstar_alloc(msg, c_msg, finalize_dbus_message);
	CAMLreturn(msg);
}
