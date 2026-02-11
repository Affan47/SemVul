wi_string_last_path_component(wi_string_t *path) {
	wi_range_t			range;
	wi_uinteger_t		length, index;

	if(wi_is_equal(path, WI_STR("/")))
		return path;

	length	= wi_string_length(path);
	range 	= wi_make_range(0, length);

	while(true) {
		index = wi_string_index_of_string_in_range(path, WI_STR("/"), WI_STRING_BACKWARDS, range);

		if(index == WI_NOT_FOUND) {
			return path;
		}
		else if(index == length - 1) {
			range.length--;

			if(range.length == 0)
				return WI_STR("/");

			continue;
		}

		return wi_string_substring_with_range(path, wi_make_range(index + 1, range.length - index - 1));
	}
}
