delete_cb(git_reference *ref, void *payload)
{
	GIT_UNUSED(payload);

	cl_git_pass(git_reference_delete(ref));
	git_reference_free(ref);

	return 0;
}
