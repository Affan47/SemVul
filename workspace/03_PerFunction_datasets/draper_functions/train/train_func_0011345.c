read_tree_internal(git_tree_cache **out,
		const char **buffer_in, const char *buffer_end, git_tree_cache *parent)
{
	git_tree_cache *tree = NULL;
	const char *name_start, *buffer;
	int count;
	size_t name_len;

	buffer = name_start = *buffer_in;

	if ((buffer = memchr(buffer, '\0', buffer_end - buffer)) == NULL)
		goto corrupted;

	if (++buffer >= buffer_end)
		goto corrupted;

	name_len = strlen(name_start);
	tree = git__malloc(sizeof(git_tree_cache) + name_len + 1);
	GITERR_CHECK_ALLOC(tree);

	memset(tree, 0x0, sizeof(git_tree_cache));
	tree->parent = parent;


	memcpy(tree->name, name_start, name_len);
	tree->name[name_len] = '\0';


	if (git__strtol32(&count, buffer, &buffer, 10) < 0 || count < -1)
		goto corrupted;

	tree->entries = count;

	if (*buffer != ' ' || ++buffer >= buffer_end)
		goto corrupted;


	if (git__strtol32(&count, buffer, &buffer, 10) < 0 || count < 0)
		goto corrupted;

	tree->children_count = count;

	if (*buffer != '\n' || ++buffer > buffer_end)
		goto corrupted;


	if (tree->entries >= 0) {

		if (buffer + GIT_OID_RAWSZ > buffer_end)
			goto corrupted;

		git_oid_fromraw(&tree->oid, (const unsigned char *)buffer);
		buffer += GIT_OID_RAWSZ;
	}


	if (tree->children_count > 0) {
		unsigned int i;

		tree->children = git__malloc(tree->children_count * sizeof(git_tree_cache *));
		GITERR_CHECK_ALLOC(tree->children);

		for (i = 0; i < tree->children_count; ++i) {
			if (read_tree_internal(&tree->children[i], &buffer, buffer_end, tree) < 0)
				return -1;
		}
	}

	*buffer_in = buffer;
	*out = tree;
	return 0;

 corrupted:
	git_tree_cache_free(tree);
	giterr_set(GITERR_INDEX, "Corruped TREE extension in index");
	return -1;
}
