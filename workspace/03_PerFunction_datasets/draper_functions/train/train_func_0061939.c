modem_find_prop(struct modem_prop *props, size_t size, const char *prop_name)
{
	struct modem_prop *prop_end;

	for (prop_end = props + size; props < prop_end; props++)
	{
		if (text_cmp(prop_name, props->name) == 0)
		{
			return props;
		}
	}

	return NULL;
}
