test_config_stress__comments(void)
{
	git_config *config;
	const char *str;

	cl_git_pass(git_config_open_ondisk(&config, cl_fixture("config/config12")));

	cl_git_pass(git_config_get_string(&str, config, "some.section.test2"));
	cl_assert_equal_s("hello", str);

	cl_git_pass(git_config_get_string(&str, config, "some.section.test3"));
	cl_assert_equal_s("welcome", str);

	cl_git_pass(git_config_get_string(&str, config, "some.section.other"));
	cl_assert_equal_s("hello! \" ; ; ; ", str);

	cl_git_pass(git_config_get_string(&str, config, "some.section.other2"));
	cl_assert_equal_s("cool! \" # # # ", str);

	cl_git_pass(git_config_get_string(&str, config, "some.section.multi"));
	cl_assert_equal_s("hi, this is a ; multiline comment # with ;\n special chars and other stuff !@#", str);

	cl_git_pass(git_config_get_string(&str, config, "some.section.multi2"));
	cl_assert_equal_s("good, this is a ; multiline comment # with ;\n special chars and other stuff !@#", str);

	cl_git_pass(git_config_get_string(&str, config, "some.section.back"));
	cl_assert_equal_s("this is \ba phrase", str);

	git_config_free(config);
}
