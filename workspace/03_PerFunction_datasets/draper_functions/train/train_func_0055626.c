read_unmerged(git_index *index, const char *buffer, size_t size)
{
	const char *endptr;
	size_t len;
	int i;

	git_vector_init(&index->unmerged, 16, unmerged_cmp);

	while (size) {
		git_index_entry_unmerged *lost;

		len = strlen(buffer) + 1;
		if (size <= len)
			return git__throw(GIT_ERROR, "Failed to read unmerged entries");

		if ((lost = git__malloc(sizeof(git_index_entry_unmerged))) == NULL)
			return GIT_ENOMEM;

		if (git_vector_insert(&index->unmerged, lost) < GIT_SUCCESS)
			return git__throw(GIT_ERROR, "Failed to read unmerged entries");

		lost->path = git__strdup(buffer);
		if (!lost->path)
			return GIT_ENOMEM;

		size -= len;
		buffer += len;

		for (i = 0; i < 3; i++) {
			if (git__strtol32((long int *) &lost->mode[i], buffer, &endptr, 8) < GIT_SUCCESS ||
				!endptr || endptr == buffer || *endptr)
				return GIT_ERROR;

			len = (endptr + 1) - (char *) buffer;
			if (size <= len)
				return git__throw(GIT_ERROR, "Failed to read unmerged entries");

			size -= len;
			buffer += len;
		}

		for (i = 0; i < 3; i++) {
			if (!lost->mode[i])
				continue;
			if (size < 20)
				return git__throw(GIT_ERROR, "Failed to read unmerged entries");
			git_oid_fromraw(&lost->oid[i], (unsigned char *) buffer);
			size -= 20;
			buffer += 20;
		}
	}

	return GIT_SUCCESS;
}
