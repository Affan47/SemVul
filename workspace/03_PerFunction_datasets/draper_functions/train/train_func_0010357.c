create_index(struct checkout_index_entry *entries, size_t entries_len)
{
	git_buf path = GIT_BUF_INIT;
	size_t i;

	for (i = 0; i < entries_len; i++) {
		git_buf_joinpath(&path, TEST_REPO_PATH, entries[i].path);

		if (entries[i].stage == 3 && (i == 0 || strcmp(entries[i-1].path, entries[i].path) != 0 || entries[i-1].stage != 2))
			p_unlink(git_buf_cstr(&path));

		git_index_remove_bypath(g_index, entries[i].path);
	}

	for (i = 0; i < entries_len; i++) {
		git_index_entry entry;

		memset(&entry, 0x0, sizeof(git_index_entry));

		entry.mode = entries[i].mode;
		entry.flags = entries[i].stage << GIT_IDXENTRY_STAGESHIFT;
		git_oid_fromstr(&entry.id, entries[i].oid_str);
		entry.path = entries[i].path;

		cl_git_pass(git_index_add(g_index, &entry));
	}

	git_buf_free(&path);
}
