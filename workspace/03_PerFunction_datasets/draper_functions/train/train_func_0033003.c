wi_mutable_string_normalize_path(wi_mutable_string_t *path) {
	wi_mutable_array_t		*array;
	wi_string_t				*component, *string;
	wi_boolean_t			absolute;
	wi_uinteger_t			i, count;

	WI_RUNTIME_ASSERT_MUTABLE(path);

	if(wi_string_length(path) == 0 || wi_is_equal(path, WI_STR("/")))
	   return;

	wi_mutable_string_expand_tilde_in_path(path);

	absolute	= wi_string_has_prefix(path, WI_STR("/"));
	array		= _wi_string_path_components(path);
	count		= wi_array_count(array);

	for(i = 0; i < count; i++) {
		component = WI_ARRAY(array, i);

		if(wi_string_length(component) == 0 || wi_is_equal(component, WI_STR("/"))) {
			wi_mutable_array_remove_data_at_index(array, i);

			i--;
			count--;
		}
		else if(wi_is_equal(component, WI_STR("."))) {
			wi_mutable_array_remove_data_at_index(array, i);

			i--;
			count--;
		}
		else if(absolute && wi_is_equal(component, WI_STR("..")) && i > 0) {
			wi_mutable_array_remove_data_at_index(array, i - 1);
			wi_mutable_array_remove_data_at_index(array, i - 1);

			i -= 2;
			count -= 2;
		}
	}

	string = wi_array_components_joined_by_string(array, WI_STR("/"));

	if(wi_string_has_prefix(path, WI_STR("/")))
		wi_mutable_string_set_format(path, WI_STR("/%@"), string);
	else
		wi_mutable_string_set_string(path, string);
}
