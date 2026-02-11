stub_dbus_message_get_type(value message)
{
	CAMLparam1(message);
	CAMLlocal1(ret);
	int c_type;

	c_type = dbus_message_get_type(DBusMessage_val(message));
	ret = Val_int(find_index_equal(c_type, __messagetype_table));
	CAMLreturn(ret);
}
