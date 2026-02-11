git_oid_shorten_new(size_t min_length)
{
	git_oid_shorten *os;

	os = git__malloc(sizeof(git_oid_shorten));
	if (os == NULL)
		return NULL;

	memset(os, 0x0, sizeof(git_oid_shorten));

	if (resize_trie(os, 16) < GIT_SUCCESS) {
		free(os);
		return NULL;
	}

	os->node_count = 1;
	os->min_length = min_length;

	return os;
}
