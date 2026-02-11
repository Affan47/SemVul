check_imported_string (char *src, int i, size_t len)
{
    int err = 0;

    if (!g_utf8_validate(src, -1, NULL)) {
	gchar *trstr = NULL;
	gsize bytes;

	trstr = g_locale_to_utf8(src, -1, NULL, &bytes, NULL);

	if (trstr == NULL) {
	    gretl_errmsg_sprintf("Invalid characters in imported string, line %d", i);
	    err = E_DATA;
	} else {
	    *src = '\0';
	    strncat(src, trstr, len - 1);
	    g_free(trstr);
	}
    }

    return err;
}
