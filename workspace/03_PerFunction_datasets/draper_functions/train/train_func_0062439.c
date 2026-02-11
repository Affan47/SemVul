magnet_parse_push_source(const char *uri, const char **error_str)
{
	struct magnet_source *ms;
	const char *p, *endptr;
	struct guid guid;

	clear_error_str(&error_str);
	g_return_val_if_fail(uri, NULL);

	p = is_strprefix(uri, "push://");
	g_return_val_if_fail(p, NULL);

	endptr = strchr(p, ':');
	if (NULL == endptr || GUID_HEX_SIZE != (endptr - p))
		endptr = strchr(p, '/');

	if (
		NULL == endptr ||
		GUID_HEX_SIZE != (endptr - p) ||
		!hex_to_guid(p, &guid)
	) {
		*error_str = "Bad GUID in push source";
		return NULL;
	}

	ms = magnet_parse_proxy_location(endptr, error_str);
	if (ms) {
		ms->guid = atom_guid_get(&guid);
	}
	return ms;
}
