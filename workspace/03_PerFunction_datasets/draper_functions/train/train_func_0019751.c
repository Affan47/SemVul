dict_valbyname(unsigned int attr, unsigned int vendor, const char *name)
{
	DICT_VALUE *my_dv, *dv;
	uint32_t buffer[(sizeof(*my_dv) + DICT_VALUE_MAX_NAME_LEN + 3)/4];

	if (!name) return NULL;

	my_dv = (DICT_VALUE *) buffer;
	my_dv->attr = attr;
	my_dv->vendor = vendor;
	my_dv->name[0] = '\0';


	dv = fr_hash_table_finddata(values_byname, my_dv);
	if (dv) my_dv->attr = dv->value;

	strlcpy(my_dv->name, name, DICT_VALUE_MAX_NAME_LEN + 1);

	return fr_hash_table_finddata(values_byname, my_dv);
}
