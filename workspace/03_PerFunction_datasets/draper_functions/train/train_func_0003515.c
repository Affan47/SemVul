stub_dbus_message_marshal(value message)
{
	CAMLparam1(message);
	CAMLlocal1(msgstr);
	char *c_msgstr;
	int c_msglen;

	if (!dbus_message_marshal(DBusMessage_val(message), &c_msgstr, &c_msglen))
		caml_raise_out_of_memory();
	msgstr = caml_alloc_string(c_msglen);
	memcpy(String_val(msgstr), c_msgstr, c_msglen);

	CAMLreturn(msgstr);
}
