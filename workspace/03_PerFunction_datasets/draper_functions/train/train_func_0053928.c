stub_dbus_message_get_header(value message)
{
	CAMLparam1(message);
	CAMLlocal2(ret, v);

	ret = caml_alloc_tuple(8);

	v = stub_dbus_message_get_serial(message);
	Store_field(ret, 0, v);

	v = stub_dbus_message_get_type(message);
	Store_field(ret, 1, v);

	v = stub_dbus_message_get_destination(message);
	Store_field(ret, 2, v);

	v = stub_dbus_message_get_path(message);
	Store_field(ret, 3, v);

	v = stub_dbus_message_get_interface(message);
	Store_field(ret, 4, v);

	v = stub_dbus_message_get_member(message);
	Store_field(ret, 5, v);

	v = stub_dbus_message_get_error_name(message);
	Store_field(ret, 6, v);

	v = stub_dbus_message_get_sender(message);
	Store_field(ret, 7, v);

	CAMLreturn(ret);
}
