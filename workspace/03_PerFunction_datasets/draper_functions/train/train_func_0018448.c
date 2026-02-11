filter_file_validate (EFilterElement *element,
                      EAlert **alert)
{
	EFilterFile *file = E_FILTER_FILE (element);

	g_warn_if_fail (alert == NULL || *alert == NULL);

	if (!file->path) {
		if (alert)
			*alert = e_alert_new ("filter:no-file", NULL);
		return FALSE;
	}


	if (g_strcmp0 (file->type, "file") == 0) {
		if (!g_file_test (file->path, G_FILE_TEST_IS_REGULAR)) {
			if (alert)
				*alert = e_alert_new ("filter:bad-file",
						       file->path, NULL);
			return FALSE;
		}
	} else if (g_strcmp0 (file->type, "command") == 0) {


		return (file->path[0] != '\0');
	}

	return TRUE;
}
