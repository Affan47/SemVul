test_index_names__cleaned_on_checkout_tree(void)
{
	git_oid oid;
	git_object *obj;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_UPDATE_ONLY;

	test_index_names__add();
	git_reference_name_to_id(&oid, repo, "refs/heads/master");
	git_object_lookup(&obj, repo, &oid, GIT_OBJ_ANY);
	git_checkout_tree(repo, obj, &opts);
	cl_assert_equal_sz(0, git_index_name_entrycount(repo_index));

	git_object_free(obj);
}
