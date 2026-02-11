test_object_tag_write__lightweight_over_existing(void)
{

	git_oid target_id, object_id, existing_object_id;
	git_object *target;

	git_oid_fromstr(&target_id, tagged_commit);
	cl_git_pass(git_object_lookup(&target, g_repo, &target_id, GIT_OBJ_COMMIT));

	cl_git_fail(git_tag_create_lightweight(
                                          &object_id,
                                          g_repo,
                                          "e90810b",
                                          target,
                                          0));

	git_oid_fromstr(&existing_object_id, tag2_id);
	cl_assert(git_oid_cmp(&object_id, &existing_object_id) == 0);

	git_object_free(target);
}
