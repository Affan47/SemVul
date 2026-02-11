test_object_tree_write__subtree(void)
{

	git_treebuilder *builder;
	git_tree *tree;
	git_oid id, bid, subtree_id, id2, id3;
	git_oid id_hiearar;

	git_oid_fromstr(&id, first_tree);
	git_oid_fromstr(&id2, second_tree);
	git_oid_fromstr(&id3, third_tree);
	git_oid_fromstr(&bid, blob_oid);


	cl_git_pass(git_treebuilder_create(&builder, NULL));
	cl_git_pass(git_treebuilder_insert(NULL,builder,"new.txt",&bid,0100644));
	cl_git_pass(git_treebuilder_write(&subtree_id, g_repo, builder));
	git_treebuilder_free(builder);


	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));
	cl_git_pass(git_treebuilder_create(&builder, tree));
	cl_git_pass(git_treebuilder_insert(NULL,builder,"new",&subtree_id,040000));
	cl_git_pass(git_treebuilder_write(&id_hiearar, g_repo, builder));
	git_treebuilder_free(builder);
	git_tree_free(tree);

	cl_assert(git_oid_cmp(&id_hiearar, &id3) == 0);


	cl_git_pass(git_tree_lookup(&tree, g_repo, &id_hiearar));
	cl_assert(2 == git_tree_entrycount(tree));
	git_tree_free(tree);
}
