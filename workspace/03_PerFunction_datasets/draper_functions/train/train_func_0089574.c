enchant_normalize_dictionary_tag (const char * const dict_tag)
{
	char * new_tag = g_strdup (dict_tag);
	char * needle;

	new_tag = g_strstrip (new_tag);


	if ((needle = strchr (new_tag, '@')) != NULL)
		*needle = '\0';


	if ((needle = strchr (new_tag, '.')) != NULL)
		*needle = '\0';


	if ((needle = strchr (new_tag, '-')) != NULL)
		*needle = '_';


	if ((needle = strchr (new_tag, '_')) != NULL) {
			enchant_ascii_strdown(new_tag, needle - new_tag);
			++needle;

			enchant_ascii_strup(needle, -1);
		}
	else {
			enchant_ascii_strdown(new_tag, -1);
		}

	return new_tag;
}
