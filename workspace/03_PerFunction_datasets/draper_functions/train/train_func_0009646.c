nautilus_file_get_default_sort_type (NautilusFile *file,
				     gboolean *reversed)
{
	NautilusFileSortType retval;
	gboolean is_recent, is_download, is_trash, is_search, res;

	retval = NAUTILUS_FILE_SORT_NONE;
	is_recent = is_download = is_trash = is_search = FALSE;
	res = get_attributes_for_default_sort_type (file, &is_recent, &is_download, &is_trash, &is_search);

	if (res) {
		if (is_recent) {
			retval = NAUTILUS_FILE_SORT_BY_ATIME;
		} else if (is_download) {
			retval = NAUTILUS_FILE_SORT_BY_MTIME;
		} else if (is_trash) {
			retval = NAUTILUS_FILE_SORT_BY_TRASHED_TIME;
		} else if (is_search) {
			retval = NAUTILUS_FILE_SORT_BY_SEARCH_RELEVANCE;
		}

		if (reversed != NULL) {
			*reversed = res;
		}
	}

	return retval;
}
