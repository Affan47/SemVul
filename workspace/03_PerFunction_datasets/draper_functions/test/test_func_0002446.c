get_header_value(Octstr *header)
{
	Octstr *h = NULL;
	long colon = -1;

	if (header == NULL) {
		error(0, "get_header_value: NULL argument");
		return NULL;
	}

	octstr_strip_blanks(header);
	colon = octstr_search_char(header, ':', 0);
	if (colon == -1) {
		error(0, "get_header_value: Malformed header (%s)", octstr_get_cstr (header));
		return NULL;
	} else {
		h = octstr_copy(header, colon + 1, octstr_len(header));
		octstr_strip_blanks(h);
	}

	debug("wap.wsp.http", 0, "get_header_value: Value (%s)", octstr_get_cstr (h));
	return h;
}
