print_pref_double(const gchar *key, gdouble fallback)
{
	gdouble value;

	if (pref_list_double_get(PRINT_PREF_GROUP, key, &value)) return value;
	return fallback;
}
