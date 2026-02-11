stf_parse_options_valid (StfParseOptions_t *parseoptions)
{
	g_return_val_if_fail (parseoptions != NULL, FALSE);

	if (parseoptions->parsetype == PARSE_TYPE_CSV) {
		if (parseoptions->stringindicator == '\0') {
			g_warning ("STF: Cannot have \\0 as string indicator");
			return FALSE;
		}

	} else if (parseoptions->parsetype == PARSE_TYPE_FIXED) {
		if (!parseoptions->splitpositions) {
			g_warning ("STF: No splitpositions in struct");
			return FALSE;
		}
	}

	return TRUE;
}
