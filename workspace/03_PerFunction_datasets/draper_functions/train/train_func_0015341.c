config_get_string(const char *sectionname, const char *keyname,
		int skip, const char *default_value)
{
	ConfigKey *k = find_key(find_section(sectionname), keyname, skip);

	if (k == NULL)
		return default_value;

	return k->value;


}
