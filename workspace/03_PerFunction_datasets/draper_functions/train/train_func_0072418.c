_nm_utils_convert_uint_array_to_string (const GValue *src_value, GValue *dest_value)
{
	GArray *array;
	GString *printable;
	guint i = 0;

	g_return_if_fail (g_type_is_a (G_VALUE_TYPE (src_value), DBUS_TYPE_G_UINT_ARRAY));

	array = (GArray *) g_value_get_boxed (src_value);

	printable = g_string_new ("[");
	while (array && (i < array->len)) {
		char buf[INET_ADDRSTRLEN + 1];
		struct in_addr addr;

		if (i > 0)
			g_string_append (printable, ", ");

		memset (buf, 0, sizeof (buf));
		addr.s_addr = g_array_index (array, guint32, i++);
		if (!inet_ntop (AF_INET, &addr, buf, INET_ADDRSTRLEN))
			g_warning ("%s: error converting IP4 address 0x%X",
			           __func__, ntohl (addr.s_addr));
		g_string_append_printf (printable, "%u (%s)", addr.s_addr, buf);
	}
	g_string_append_c (printable, ']');

	g_value_take_string (dest_value, printable->str);
	g_string_free (printable, FALSE);
}
