git_treebuilder_clear(git_treebuilder *bld)
{
	size_t i;
	assert(bld);

	for (i = 0; i < bld->entries.length; ++i) {
		git_tree_entry *e = bld->entries.contents[i];
		free(e->filename);
		free(e);
	}

	git_vector_clear(&bld->entries);
}
