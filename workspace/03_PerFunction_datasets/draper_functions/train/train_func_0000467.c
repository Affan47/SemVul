write_entries(git_index *index, git_filebuf *file)
{
	int error = 0;
	size_t i;
	git_vector case_sorted, *entries;
	git_index_entry *entry;

	if (git_mutex_lock(&index->lock) < 0) {
		giterr_set(GITERR_OS, "Failed to lock index");
		return -1;
	}


	if (index->ignore_case) {
		git_vector_dup(&case_sorted, &index->entries, git_index_entry_cmp);
		git_vector_sort(&case_sorted);
		entries = &case_sorted;
	} else {
		entries = &index->entries;
	}

	git_vector_foreach(entries, i, entry)
		if ((error = write_disk_entry(file, entry)) < 0)
			break;

	git_mutex_unlock(&index->lock);

	if (index->ignore_case)
		git_vector_free(&case_sorted);

	return error;
}
