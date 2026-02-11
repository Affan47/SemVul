test_config_write__write_subsection(void)
{
	git_config *cfg;
	const char *str;

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_set_string(cfg, "my.own.var", "works"));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_get_string(&str, cfg, "my.own.var"));
	cl_git_pass(strcmp(str, "works"));
	git_config_free(cfg);
}
