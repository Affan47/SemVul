test_status_ignore__add_internal_as_first_thing(void)
{
	const char *add_me = "\n#################\n## Eclipse\n#################\n\n*.pydevproject\n.project\n.metadata\nbin/\ntmp/\n*.tmp\n\n";

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_pass(git_ignore_add_rule(g_repo, add_me));

	assert_is_ignored("one.tmp");
	refute_is_ignored("two.bar");
}
