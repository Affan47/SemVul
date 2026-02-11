dcc_str2type(const char *str)
{
	if (gslist_find_string(dcc_types, str) == NULL)
		return -1;

        return module_get_uniq_id_str("DCC", str);
}
