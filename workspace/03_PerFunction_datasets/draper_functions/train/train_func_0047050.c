eel_check_string_result (char *result, const char *expected)
{
	gboolean match;


	if (expected == NULL) {
		match = result == NULL;
	} else {
		match = result != NULL && strcmp (result, expected) == 0;
	}

	if (!match) {
		eel_report_check_failure (result, g_strdup (expected));
	} else {
		g_free (result);
	}
	eel_after_check ();
}
