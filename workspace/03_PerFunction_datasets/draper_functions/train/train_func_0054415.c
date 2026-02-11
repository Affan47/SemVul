git_index_add(git_index *index, const char *filename, int stage)
{
	git_index_entry entry;
	size_t path_length;

	memset(&entry, 0x0, sizeof(git_index_entry));

	path_length = strlen(filename);

	if (path_length < GIT_IDXENTRY_NAMEMASK)
		entry.flags |= path_length;
	else
		entry.flags |= GIT_IDXENTRY_NAMEMASK;;

	if (stage < 0 || stage > 3)
		return GIT_ERROR;

	entry.flags |= (stage << GIT_IDXENTRY_STAGESHIFT);

	entry.path = git__strdup(filename);

	return git_index__append(index, &entry);
}
