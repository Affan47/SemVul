test_object_raw_compare__compare_pathfmt_oids(void)
{
	const char *exp1 = "16a0123456789abcdef4b775213c23a8bd74f5e0";
	const char *exp2 = "16/a0123456789abcdef4b775213c23a8bd74f5e0";
	git_oid in;
	char out[GIT_OID_HEXSZ + 2];

	cl_git_pass(git_oid_fromstr(&in, exp1));


	out[GIT_OID_HEXSZ + 1] = 'Z';
	git_oid_pathfmt(out, &in);
	cl_assert(out[GIT_OID_HEXSZ + 1] == 'Z');


	out[GIT_OID_HEXSZ + 1] = '\0';
	cl_assert_equal_s(exp2, out);
}
