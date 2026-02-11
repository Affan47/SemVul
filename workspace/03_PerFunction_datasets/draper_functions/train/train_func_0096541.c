find_mode(const char *name)
{
	int i = index_in_strings(mode_name, name);
	return i >= 0 ? &mode_info[i] : NULL;
}
