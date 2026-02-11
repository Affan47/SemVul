gm_mcp_process_keyval(GList **info, gchar const *line) {
	gchar const *keystart;
	gchar const *valuestart;
	int keylen, valuelen;
	GmKeyValuePair *newKeyValue;

	if (*line != ' ' || line[1] == '\0' || line[1] == ' ') {
		return NULL;
	}

	keystart = ++line;
	gm_string_skip_till(&line, ": ");

	if (*line != ':') {
		return NULL;
	}

	keylen = line - keystart;
	line = g_utf8_next_char(line);

	if (line[1] == '\0' || *line != ' ') {
		return NULL;
	}

	line = g_utf8_next_char(line);

	if (*line == ' ') {
		return NULL;
	}

	valuestart = line;

	if (*line == '"') {
		++valuestart;
		++line;

		while (*line != '\0' && *line != '"') {
			if (*line == '\\') {
				++line;
			}

			++line;
		}

		valuelen = line - valuestart;

		if (*line != '"') {
			--valuelen;
		} else {
			++line;
		}
	} else {
		gm_string_skip_nonspace(&line);
		valuelen = line - valuestart;
	}

	newKeyValue = g_new(GmKeyValuePair, 1);
	newKeyValue->key = g_strndup(keystart, keylen);
	newKeyValue->value = gm_mcp_un_escape(g_strndup(valuestart, valuelen));

	*info = g_list_append(*info, newKeyValue);

	return line;
}
