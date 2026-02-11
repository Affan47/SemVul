wi_date_init_with_rfc3339_string(wi_date_t *date, wi_string_t *string) {
	wi_mutable_string_t		*fullstring;
	wi_string_t				*timezone;

	if(wi_string_length(string) >= 19) {
		fullstring	= wi_autorelease(wi_mutable_copy(string));
		timezone	= wi_string_substring_from_index(fullstring, 19);

		if(wi_is_equal(timezone, WI_STR("Z"))) {
			wi_mutable_string_delete_characters_in_range(fullstring, wi_make_range(19, 1));

			return wi_date_init_with_string(date, fullstring, WI_STR("%Y-%m-%dT%H:%M:%S"));
		}
		else if(wi_string_length(timezone) == 6) {
			wi_mutable_string_delete_characters_in_range(fullstring, wi_make_range(22, 1));

			return wi_date_init_with_string(date, fullstring, WI_STR("%Y-%m-%dT%H:%M:%S%z"));
		}
	}

	wi_release(date);

	return NULL;
}
