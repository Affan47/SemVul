git_treebuilder_create(git_treebuilder **builder_p, const git_tree *source)
{
	git_treebuilder *bld;
	size_t i, source_entries = DEFAULT_TREE_SIZE;

	assert(builder_p);

	bld = git__calloc(1, sizeof(git_treebuilder));
	if (bld == NULL)
		return GIT_ENOMEM;

	if (source != NULL)
		source_entries = source->entries.length;

	if (git_vector_init(&bld->entries, source_entries, entry_sort_cmp) < GIT_SUCCESS) {
		free(bld);
		return GIT_ENOMEM;
	}

	if (source != NULL) {
		bld->entry_count = source_entries;
		for (i = 0; i < source->entries.length; ++i) {
			git_tree_entry *entry_src = source->entries.contents[i];
			git_tree_entry *entry = git__calloc(1, sizeof(git_tree_entry));

			if (entry == NULL) {
				git_treebuilder_free(bld);
				return GIT_ENOMEM;
			}

			entry->filename = git__strdup(entry_src->filename);

			if (entry->filename == NULL) {
				free(entry);
				git_treebuilder_free(bld);
				return GIT_ENOMEM;
			}

			entry->filename_len = entry_src->filename_len;
			git_oid_cpy(&entry->oid, &entry_src->oid);
			entry->attr = entry_src->attr;

			git_vector_insert(&bld->entries, entry);
		}
	}

	*builder_p = bld;
	return GIT_SUCCESS;
}
