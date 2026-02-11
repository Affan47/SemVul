test_object_tree_write__sorted_subtrees(void)
{
	git_treebuilder *builder;
	unsigned int i;
	int position_c = -1, position_cake = -1, position_config = -1;

	struct {
		unsigned int attr;
		const char *filename;
	} entries[] = {
		{ GIT_FILEMODE_BLOB, ".gitattributes" },
	  	{ GIT_FILEMODE_BLOB, ".gitignore" },
	  	{ GIT_FILEMODE_BLOB, ".htaccess" },
	  	{ GIT_FILEMODE_BLOB, "Capfile" },
	  	{ GIT_FILEMODE_BLOB, "Makefile"},
	  	{ GIT_FILEMODE_BLOB, "README"},
	  	{ GIT_FILEMODE_TREE, "app"},
	  	{ GIT_FILEMODE_TREE, "cake"},
	  	{ GIT_FILEMODE_TREE, "config"},
	  	{ GIT_FILEMODE_BLOB, "c"},
	  	{ GIT_FILEMODE_BLOB, "git_test.txt"},
	  	{ GIT_FILEMODE_BLOB, "htaccess.htaccess"},
	  	{ GIT_FILEMODE_BLOB, "index.php"},
	  	{ GIT_FILEMODE_TREE, "plugins"},
	  	{ GIT_FILEMODE_TREE, "schemas"},
	  	{ GIT_FILEMODE_TREE, "ssl-certs"},
	  	{ GIT_FILEMODE_TREE, "vendors"}
	};

	git_oid blank_oid, tree_oid;

	memset(&blank_oid, 0x0, sizeof(blank_oid));

	cl_git_pass(git_treebuilder_create(&builder, NULL));

	for (i = 0; i < ARRAY_SIZE(entries); ++i) {
		cl_git_pass(git_treebuilder_insert(NULL,
			builder, entries[i].filename, &blank_oid, entries[i].attr));
	}

	cl_git_pass(git_treebuilder_write(&tree_oid, g_repo, builder));

	for (i = 0; i < builder->entries.length; ++i) {
		git_tree_entry *entry = git_vector_get(&builder->entries, i);

		if (strcmp(entry->filename, "c") == 0)
			position_c = i;

		if (strcmp(entry->filename, "cake") == 0)
			position_cake = i;

		if (strcmp(entry->filename, "config") == 0)
			position_config = i;
	}

	cl_assert(position_c != -1);
	cl_assert(position_cake != -1);
	cl_assert(position_config != -1);

	cl_assert(position_c < position_cake);
	cl_assert(position_cake < position_config);

	git_treebuilder_free(builder);
}
