commit_quick_parse(git_revwalk *walk, commit_object *commit, git_rawobj *raw)
{
	const int parent_len = STRLEN("parent ") + GIT_OID_HEXSZ + 1;

	unsigned char *buffer = raw->data;
	unsigned char *buffer_end = buffer + raw->len;
	unsigned char *parents_start;

	int i, parents = 0;

	buffer += STRLEN("tree ") + GIT_OID_HEXSZ + 1;

	parents_start = buffer;
	while (buffer + parent_len < buffer_end && memcmp(buffer, "parent ", STRLEN("parent ")) == 0) {
		parents++;
		buffer += parent_len;
	}

	commit->parents = alloc_parents(commit, parents);
	if (commit->parents == NULL)
		return GIT_ENOMEM;

	buffer = parents_start;
	for (i = 0; i < parents; ++i) {
		git_oid oid;

		if (git_oid_mkstr(&oid, (char *)buffer + STRLEN("parent ")) < GIT_SUCCESS)
			return GIT_EOBJCORRUPTED;

		commit->parents[i] = commit_lookup(walk, &oid);
		if (commit->parents[i] == NULL)
			return GIT_ENOMEM;

		buffer += parent_len;
	}

	commit->out_degree = (unsigned short)parents;

	if ((buffer = memchr(buffer, '\n', buffer_end - buffer)) == NULL)
		return GIT_EOBJCORRUPTED;

	buffer = memchr(buffer, '>', buffer_end - buffer);
	if (buffer == NULL)
		return GIT_EOBJCORRUPTED;

	commit->time = strtol((char *)buffer + 2, NULL, 10);
	if (commit->time == 0)
		return GIT_EOBJCORRUPTED;

	commit->parsed = 1;
	return GIT_SUCCESS;
}
