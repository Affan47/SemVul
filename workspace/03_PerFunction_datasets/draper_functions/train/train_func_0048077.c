parameter_index_from_name (const char *param_name)
{
	int i;
	for (i=0; i<SIZEOF_ARRAY(param_names); i++) {
		if (strcmp (param_name, param_names[i]) == 0) {
			return i;
		}
	}
	return -1;
}
