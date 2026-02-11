test_repo_init__reinit_overwrites_filemode(void)
{
    git_config *config;
    int expected, current_value;

#ifdef GIT_WIN32
    expected = false;
#else
    expected = true;
#endif


    cl_set_cleanup(&cleanup_repository, "overwrite.git");
    cl_git_pass(git_repository_init(&_repo, "overwrite.git", 1));


    git_repository_config(&config, _repo);
    git_config_set_bool(config, "core.filemode", !expected);
    git_config_free(config);
    git_repository_free(_repo);
    _repo = NULL;


    cl_git_pass(git_repository_init(&_repo, "overwrite.git", 1));
    git_repository_config(&config, _repo);


    cl_git_pass(git_config_get_bool(&current_value, config, "core.filemode"));
    cl_assert_equal_i(expected, current_value);

    git_config_free(config);
}
