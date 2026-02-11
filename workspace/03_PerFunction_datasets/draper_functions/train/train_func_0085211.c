metadata_check_key(const gchar *keys[], const gchar *key)
{
	const gchar **k = keys;

	while (*k)
		{
		if (strcmp(key, *k) == 0) return TRUE;
		k++;
		}
	return FALSE;
}
