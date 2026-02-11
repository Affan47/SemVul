e_credentials_new_args (const gchar *key,
                        ...)
{
	ECredentials *credentials;
	va_list va;


	g_return_val_if_fail (key != NULL, NULL);

	credentials = e_credentials_new ();

	va_start (va, key);

	while (key) {
		const gchar *value = va_arg (va, const gchar *);

		if (key && *key && value && *value)
			e_credentials_set (credentials, key, value);

		key = va_arg (va, const gchar *);
	}

	va_end (va);

	return credentials;
}
