stub_dbus_connection_get_max_message_size(value bus)
{
	CAMLparam1(bus);
	long ret;
	ret = dbus_connection_get_max_message_size(DBusConnection_val(bus));
	CAMLreturn(Val_int(ret));
}
