g_mime_header_iter_set_value (GMimeHeaderIter *iter, const char *value)
{
	g_return_val_if_fail (iter != NULL, FALSE);

	if (!g_mime_header_iter_is_valid (iter))
		return FALSE;

	g_free (iter->cursor->value);
	iter->cursor->value = g_strdup (value);

	g_mime_header_list_set_stream (iter->hdrlist, NULL);

	return TRUE;
}
