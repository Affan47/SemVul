git_status_foreach(git_repository *repo, int (*callback)(const char *, unsigned int, void *), void *payload)
{
	git_vector entries;
	struct status_entry *e;
	git_index *index;
	unsigned int i, cnt;
	git_index_entry *index_entry;
	char temp_path[GIT_PATH_MAX];
	git_oid zero;
	int error;
	git_tree *tree;
	struct status_st dirent_st;

	git_reference *head_ref, *resolved_head_ref;
	git_commit *head_commit;

	git_repository_index(&index, repo);

	cnt = git_index_entrycount(index);
	git_vector_init(&entries, cnt, status_cmp);
	for (i = 0; i < cnt; ++i) {
		index_entry = git_index_get(index, i);

		e = new_status_entry(&entries, index_entry->path);
		git_oid_cpy(&e->index_oid, &index_entry->oid);
		e->mtime = index_entry->mtime;
	}

	git_reference_lookup(&head_ref, repo, GIT_HEAD_FILE);
	git_reference_resolve(&resolved_head_ref, head_ref);

	git_commit_lookup(&head_commit, repo, git_reference_oid(resolved_head_ref));


	git_commit_tree(&tree, head_commit);
	recurse_tree_entries(tree, &entries, "");

	dirent_st.workdir_path_len = strlen(repo->path_workdir);
	dirent_st.entry.vector = &entries;
	strcpy(temp_path, repo->path_workdir);
	git_futils_direach(temp_path, GIT_PATH_MAX, dirent_cb, &dirent_st);

	memset(&zero, 0x0, sizeof(git_oid));
	for (i = 0; i < entries.length; ++i) {
		e = (struct status_entry *)git_vector_get(&entries, i);

		set_status_flags(e);
	}


	for (i = 0; i < entries.length; ++i) {
		e = (struct status_entry *)git_vector_get(&entries, i);

		if ((error = callback(e->path, e->status_flags, payload)) < GIT_SUCCESS)
			return git__throw(error, "Failed to list statuses. User callback failed");
	}

	for (i = 0; i < entries.length; ++i) {
		e = (struct status_entry *)git_vector_get(&entries, i);
		free(e);
	}
	git_vector_free(&entries);

	return GIT_SUCCESS;
}
