note_list_cb(
	const git_oid *blob_id, const git_oid *annotated_obj_id, void *payload)
{
	git_oid expected_note_oid, expected_target_oid;

	unsigned int *count = (unsigned int *)payload;

	cl_assert(*count < EXPECTATIONS_COUNT);

	cl_git_pass(git_oid_fromstr(&expected_note_oid, list_expectations[*count].note_sha));
	cl_assert(git_oid_cmp(&expected_note_oid, blob_id) == 0);

	cl_git_pass(git_oid_fromstr(&expected_target_oid, list_expectations[*count].annotated_object_sha));
	cl_assert(git_oid_cmp(&expected_target_oid, annotated_obj_id) == 0);

	(*count)++;

	return 0;
}
