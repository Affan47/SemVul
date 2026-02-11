ao_bookmark_list_update_marker(AoBookmarkList *bm, GeanyEditor *editor, SCNotification *nt)
{
	AoBookmarkListPrivate *priv = AO_BOOKMARK_LIST_GET_PRIVATE(bm);

	if (priv->enable_bookmarklist &&
		nt->nmhdr.code == SCN_MODIFIED && nt->modificationType == SC_MOD_CHANGEMARKER)
	{
		if (sci_is_marker_set_at_line(editor->sci, nt->line, 1))
		{
			add_line(bm, editor->sci, nt->line);
		}
		else
		{
			delete_line(bm, nt->line);
		}
	}
}
