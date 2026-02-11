xkl_config_registry_search_by_pattern_in_layout(XklConfigRegistry * config,
						const XklConfigItem * item,
						SearchParamType *
						search_param)
{
	gchar *upper_name = g_ascii_strup(item->name, -1);

	xkl_debug(200, "Layout to check: [%s][%s]\n", item->name,
		  item->description);

	search_param->country_matched =
	    search_param->language_matched = FALSE;

	if (if_country_matches_pattern(item, search_param->patterns, TRUE))
		search_param->country_matched = TRUE;
	else if (if_language_matches_pattern
		 (item, search_param->patterns, TRUE))
		search_param->language_matched = TRUE;
	else if (search_all(item->description, search_param->patterns))
		search_param->language_matched = TRUE;

	if (search_param->country_matched
	    || search_param->language_matched)
		(search_param->func) (config, item, NULL,
				      search_param->data);

	search_param->layout_item = item;

	xkl_config_registry_foreach_layout_variant(config, item->name,
						   (XklConfigItemProcessFunc)
						   xkl_config_registry_search_by_pattern_in_variant,
						   search_param);

	g_free(upper_name);
}
