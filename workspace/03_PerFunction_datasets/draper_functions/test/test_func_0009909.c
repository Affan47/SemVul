is_scheme_supported (NautilusConnectServerDialog *dialog,
		     const char                  *scheme)
{
	int i;

	if (dialog->details->supported == NULL) {
		return FALSE;
	}

	for (i = 0; dialog->details->supported[i] != NULL; i++) {
		if (strcmp (scheme, dialog->details->supported[i]) == 0) {
			return TRUE;
		}
	}

	return FALSE;
}
