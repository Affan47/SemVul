test_config_read__escaping_quotes(void)
{
	git_config *cfg;
	const char *str;

	cl_git_pass(git_config_open_ondisk(&cfg, cl_fixture("config/config13")));
	cl_git_pass(git_config_get_string(&str, cfg, "core.editor"));
	cl_assert_equal_s("\"C:/Program Files/Nonsense/bah.exe\" \"--some option\"", str);

	git_config_free(cfg);
}
