advsearch_search_msgs_in_folders(AdvancedSearch* search, MsgInfoList **messages,
				          FolderItem* folderItem, gboolean recursive)
{
	if (search == NULL || search->predicate == NULL)
		return FALSE;

	search->search_aborted = FALSE;
	return search_impl(messages, search, folderItem, recursive);
}
