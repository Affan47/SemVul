diff_context_line__pattern_match(
	git_diff_driver *driver, const char *line, size_t line_len)
{
	size_t i;

	GIT_UNUSED(line_len);

	for (i = 0; i < git_array_size(driver->fn_patterns); ++i) {
		if (!regexec(git_array_get(driver->fn_patterns, i), line, 0, NULL, 0))
			return true;
	}

	return false;
}
