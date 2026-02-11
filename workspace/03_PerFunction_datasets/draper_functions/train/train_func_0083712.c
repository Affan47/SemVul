nm_utils_ip6_addresses_to_gvalue (GSList *list, GValue *value)
{
	GPtrArray *addresses;
	GSList *iter;

	addresses = g_ptr_array_new ();

	for (iter = list; iter; iter = iter->next) {
		NMIP6Address *addr = (NMIP6Address *) iter->data;
		GValueArray *array;
		GValue element = {0, };
		GByteArray *ba;

		array = g_value_array_new (3);


		g_value_init (&element, DBUS_TYPE_G_UCHAR_ARRAY);
		ba = g_byte_array_new ();
		g_byte_array_append (ba, (guint8 *) nm_ip6_address_get_address (addr), 16);
		g_value_take_boxed (&element, ba);
		g_value_array_append (array, &element);
		g_value_unset (&element);


		g_value_init (&element, G_TYPE_UINT);
		g_value_set_uint (&element, nm_ip6_address_get_prefix (addr));
		g_value_array_append (array, &element);
		g_value_unset (&element);


		g_value_init (&element, DBUS_TYPE_G_UCHAR_ARRAY);
		ba = g_byte_array_new ();
		g_byte_array_append (ba, (guint8 *) nm_ip6_address_get_gateway (addr), 16);
		g_value_take_boxed (&element, ba);
		g_value_array_append (array, &element);
		g_value_unset (&element);

		g_ptr_array_add (addresses, array);
	}

	g_value_take_boxed (value, addresses);
}
