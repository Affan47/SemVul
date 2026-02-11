rev_list_view_can_copy (GiggleClipboard *clipboard)
{
	gboolean result = FALSE;
	GList   *selection, *l;

	selection = giggle_rev_list_view_get_selection (GIGGLE_REV_LIST_VIEW (clipboard));

	for (l = selection; l; l = l->next) {
		if (selection->data && giggle_revision_get_sha (selection->data)) {
			result = TRUE;
			break;
		}
	}

	while (selection) {
		if (selection->data)
			g_object_unref (selection->data);

		selection = g_list_delete_link (selection, selection);
	}

	return result;
}
