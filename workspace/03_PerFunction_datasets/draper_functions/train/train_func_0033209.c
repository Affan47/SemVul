test_config_multivar__get(void)
{
	git_config *cfg;
	int n;

	cl_git_pass(git_config_open_ondisk(&cfg, "config/config11"));

	n = 0;
	cl_git_pass(git_config_get_multivar(cfg, _name, NULL, cb, &n));
	cl_assert(n == 2);

	n = 0;
	cl_git_pass(git_config_get_multivar(cfg, _name, "example", cb, &n));
	cl_assert(n == 1);

	git_config_free(cfg);
}
