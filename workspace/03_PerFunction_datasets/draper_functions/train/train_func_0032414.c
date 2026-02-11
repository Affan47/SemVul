lt_region_dump(const lt_region_t *region)
{
	lt_string_t *string = lt_string_new(NULL);
	const char *preferred = lt_region_get_preferred_tag(region);

	if (preferred) {
		if (lt_string_length(string) == 0)
			lt_string_append(string, " (");
		lt_string_append_printf(string, "preferred-value: %s", preferred);
	}
	if (lt_string_length(string) > 0)
		lt_string_append(string, ")");

	lt_info("Region: %s [%s]%s",
		lt_region_get_tag(region),
		lt_region_get_name(region),
		lt_string_value(string));

	lt_string_unref(string);
}
