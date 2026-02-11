can_accept_items_as_bookmarks (const GList *items)
{
	int max;
	char *uri;
	NemoFile *file;


	for (max = 100; items != NULL && max >= 0; items = items->next, max--) {
		uri = ((NemoDragSelectionItem *)items->data)->uri;
		file = nemo_file_get_by_uri (uri);
		if (!can_accept_file_as_bookmark (file)) {
			nemo_file_unref (file);
			return FALSE;
		}
		nemo_file_unref (file);
	}

	return TRUE;
}
