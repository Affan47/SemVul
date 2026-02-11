_gdata_service_secure_strndup (const gchar *str, gsize n_bytes)
{
#ifdef HAVE_GNOME
	gsize str_len;
	GDataSecureString duped_str;

	if (str == NULL) {
		return NULL;
	}

	str_len = MIN (strlen (str), n_bytes);
	duped_str = (GDataSecureString) gcr_secure_memory_alloc (str_len + 1);
	strncpy (duped_str, str, str_len);
	*(duped_str + str_len) = '\0';

	return duped_str;
#else
	return g_strndup (str, n_bytes);
#endif
}
