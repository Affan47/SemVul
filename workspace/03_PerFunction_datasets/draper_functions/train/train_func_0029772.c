_nc_build_names(struct name_table_entry **actual,
		const name_table_data *source,
		const char *strings)
{
	if (*actual == 0) {
		*actual = typeCalloc(struct name_table_entry, CAPTABSIZE);
		if (*actual != 0) {
			unsigned n;
			unsigned len = 0;
			for (n = 0; n < CAPTABSIZE; ++n) {
				(*actual)[n].nte_name = strings + len;
				(*actual)[n].nte_type = source[n].nte_type;
				(*actual)[n].nte_index = source[n].nte_index;
				(*actual)[n].nte_link = source[n].nte_link;
				next_string(strings, &len);
			}
		}
	}
	return *actual;
}
