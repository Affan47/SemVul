stub_dbus_message_set_reply_serial(value message, value serial)
{
	CAMLparam2(message, serial);
	unsigned int c_serial = Int32_val(serial);

	dbus_message_set_reply_serial(DBusMessage_val(message), c_serial);
	CAMLreturn(Val_unit);
}
