test_object_raw_hash__hash_buffer_in_single_call(void)
{
	git_oid id1, id2;

	cl_git_pass(git_oid_fromstr(&id1, hello_id));
	git_hash_buf(&id2, hello_text, strlen(hello_text));
	cl_assert(git_oid_cmp(&id1, &id2) == 0);
}
