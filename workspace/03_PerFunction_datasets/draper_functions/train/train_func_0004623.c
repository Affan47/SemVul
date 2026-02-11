convert_string_value (EBookBackendSqliteDB *ebsdb,
                      const gchar *value,
                      const gchar *region,
                      ConvertFlags flags,
                      MatchType match)
{
	GString *str;
	size_t len;
	gchar c;
	gboolean escape_modifier_needed = FALSE;
	const gchar *escape_modifier = " ESCAPE '^'";
	gchar *computed = NULL;
	gchar *normal;
	const gchar *ptr;

	g_return_val_if_fail (value != NULL, NULL);

	if ((flags & CONVERT_NORMALIZE) && match != MATCH_REGEX)
		normal = e_util_utf8_normalize (value);
	else
		normal = g_strdup (value);


	len = strlen (normal);
	str = g_string_sized_new (2 * len + 4 + strlen (escape_modifier) - 1);
	g_string_append_c (str, '\'');

	switch (match) {
	case MATCH_CONTAINS:
	case MATCH_ENDS_WITH:
	case MATCH_SHORT_PHONE_NUMBER:
		g_string_append_c (str, '%');
		break;

	case MATCH_BEGINS_WITH:
	case MATCH_IS:
	case MATCH_PHONE_NUMBER:
	case MATCH_NATIONAL_PHONE_NUMBER:
	case MATCH_REGEX:
		break;
	}

	if (flags & CONVERT_REVERSE) {
		computed = g_utf8_strreverse (normal, -1);
		ptr = computed;
	} else if (flags & CONVERT_PHONE) {
		computed = convert_phone (normal, region);
		ptr = computed;
	} else {
		ptr = normal;
	}

	while ((c = *ptr++)) {
		if (c == '\'') {
			g_string_append_c (str, '\'');
		} else if ((c == '%' || c == '^') && match != MATCH_REGEX) {
			g_string_append_c (str, '^');
			escape_modifier_needed = TRUE;
		}

		g_string_append_c (str, c);
	}

	switch (match) {
	case MATCH_CONTAINS:
	case MATCH_BEGINS_WITH:
		g_string_append_c (str, '%');
		break;

	case MATCH_ENDS_WITH:
	case MATCH_IS:
	case MATCH_PHONE_NUMBER:
	case MATCH_NATIONAL_PHONE_NUMBER:
	case MATCH_SHORT_PHONE_NUMBER:
	case MATCH_REGEX:
		break;
	}

	g_string_append_c (str, '\'');

	if (escape_modifier_needed)
		g_string_append (str, escape_modifier);

	g_free (computed);
	g_free (normal);

	return g_string_free (str, FALSE);
}
