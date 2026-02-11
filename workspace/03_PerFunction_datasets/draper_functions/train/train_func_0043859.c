check_plugin(struct connman_plugin_desc *desc,
				char **patterns, char **excludes)
{
	if (excludes) {
		for (; *excludes; excludes++)
			if (g_pattern_match_simple(*excludes, desc->name))
				break;
		if (*excludes) {
			connman_info("Excluding %s", desc->description);
			return FALSE;
		}
	}

	if (patterns) {
		for (; *patterns; patterns++)
			if (g_pattern_match_simple(*patterns, desc->name))
				break;
		if (!*patterns) {
			connman_info("Ignoring %s", desc->description);
			return FALSE;
		}
	}

	return TRUE;
}
