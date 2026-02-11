test_object_raw_compare__compare_allocfmt_oids(void)
{
	const char *exp = "16a0123456789abcdef4b775213c23a8bd74f5e0";
	git_oid in;
	char *out;

	cl_git_pass(git_oid_fromstr(&in, exp));

	out = git_oid_allocfmt(&in);
	cl_assert(out);
	cl_assert_equal_s(exp, out);
	git__free(out);
}
