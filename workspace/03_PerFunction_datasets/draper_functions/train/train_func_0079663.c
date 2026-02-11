eel_str_capitalize (const char *string)
{
	char *capitalized;

	if (string == NULL) {
		return NULL;
	}

	capitalized = g_strdup (string);

	capitalized[0] = g_ascii_toupper (capitalized[0]);

	return capitalized;
}
