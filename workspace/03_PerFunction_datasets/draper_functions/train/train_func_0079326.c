stub_dbus_bus_has_owner(value bus, value name)
{
	CAMLparam2(bus, name);
	DBusError error;
	int ret;

	dbus_error_init(&error);
	ret = dbus_bus_name_has_owner(DBusConnection_val(bus), String_val(name), &error);
	if (ret != TRUE && dbus_error_is_set(&error))
		raise_dbus_error(&error);
	CAMLreturn(Val_bool(ret == TRUE));
}
