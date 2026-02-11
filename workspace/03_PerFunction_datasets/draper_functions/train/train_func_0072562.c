test_index_conflicts__get(void)
{
	const git_index_entry *conflict_entry[3];
	git_oid oid;

	cl_git_pass(git_index_conflict_get(&conflict_entry[0], &conflict_entry[1],
		&conflict_entry[2], repo_index, "conflicts-one.txt"));

	cl_assert_equal_s("conflicts-one.txt", conflict_entry[0]->path);

	git_oid_fromstr(&oid, CONFLICTS_ONE_ANCESTOR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[0]->id);

	git_oid_fromstr(&oid, CONFLICTS_ONE_OUR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[1]->id);

	git_oid_fromstr(&oid, CONFLICTS_ONE_THEIR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[2]->id);

	cl_git_pass(git_index_conflict_get(&conflict_entry[0], &conflict_entry[1],
		&conflict_entry[2], repo_index, "conflicts-two.txt"));

	cl_assert_equal_s("conflicts-two.txt", conflict_entry[0]->path);

	git_oid_fromstr(&oid, CONFLICTS_TWO_ANCESTOR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[0]->id);

	git_oid_fromstr(&oid, CONFLICTS_TWO_OUR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[1]->id);

	git_oid_fromstr(&oid, CONFLICTS_TWO_THEIR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[2]->id);
}
