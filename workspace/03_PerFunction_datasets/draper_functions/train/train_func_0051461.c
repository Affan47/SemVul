assert_peel(
	const char *sha,
	git_otype requested_type,
	const char* expected_sha,
	git_otype expected_type)
{
	git_oid oid, expected_oid;
	git_object *obj;
	git_object *peeled;

	cl_git_pass(git_oid_fromstr(&oid, sha));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJ_ANY));

	cl_git_pass(git_object_peel(&peeled, obj, requested_type));

	cl_git_pass(git_oid_fromstr(&expected_oid, expected_sha));
	cl_assert_equal_i(0, git_oid_cmp(&expected_oid, git_object_id(peeled)));

	cl_assert_equal_i(expected_type, git_object_type(peeled));

	git_object_free(peeled);
	git_object_free(obj);
}
