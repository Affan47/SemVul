soup_auth_manager_extract_challenge (const char *challenges, const char *scheme)
{
	GSList *items, *i, *next;
	int schemelen = strlen (scheme);
	char *item;
	GString *challenge;

	items = soup_header_parse_list (challenges);


	for (i = items; i; i = next_challenge_start (i->next)) {
		item = i->data;
		if (!g_ascii_strncasecmp (item, scheme, schemelen) &&
		    (!item[schemelen] || g_ascii_isspace (item[schemelen])))
			break;
	}
	if (!i) {
		soup_header_free_list (items);
		return NULL;
	}

	next = next_challenge_start (i->next);
	challenge = g_string_new (item);
	for (i = i->next; i != next; i = i->next) {
		item = i->data;
		g_string_append (challenge, ", ");
		g_string_append (challenge, item);
	}

	soup_header_free_list (items);
	return g_string_free (challenge, FALSE);
}
