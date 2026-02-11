get_custom_mod (MonoImage *m, const char *ptr, char **return_value)
{
	char *s;
	const char *mod;

	*return_value = NULL;
	while ((*ptr == MONO_TYPE_CMOD_OPT) ||
		   (*ptr == MONO_TYPE_CMOD_REQD)) {
		mod = (*ptr == MONO_TYPE_CMOD_REQD) ? "modreq" : "modopt";
		ptr++;
		ptr = get_encoded_typedef_or_ref (m, ptr, &s);

		if (*return_value == NULL)
			*return_value = g_strconcat (" ", mod, " (", s, ")", NULL);
		else
			*return_value = g_strconcat (*return_value, " ", mod, " (", s, ")", NULL);
		g_free (s);
	}
	return ptr;
}
