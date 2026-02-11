get_language (void)
{
	const char * const *langs_pointer;
	int i;

	langs_pointer = g_get_language_names ();
	for (i = 0; langs_pointer[i] != NULL; i++) {

		if (strchr (langs_pointer[i], '.') == NULL) {
		return langs_pointer[i];
		}
	}
	return NULL;
}
