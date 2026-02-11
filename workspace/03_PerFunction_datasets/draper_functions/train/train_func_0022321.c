camel_internet_address_find_name (CamelInternetAddress *addr,
                                  const gchar *name,
                                  const gchar **addressp)
{
	struct _address *a;
	gint i, len;

	g_assert (CAMEL_IS_INTERNET_ADDRESS (addr));

	len = ((CamelAddress *) addr)->addresses->len;
	for (i = 0; i < len; i++) {
		a = g_ptr_array_index (((CamelAddress *) addr)->addresses, i);
		if (a->name && !strcmp (a->name, name)) {
			if (addressp)
				*addressp = a->address;
			return i;
		}
	}
	return -1;
}
