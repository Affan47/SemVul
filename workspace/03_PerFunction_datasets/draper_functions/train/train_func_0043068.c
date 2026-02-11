git_mwindow_files_init(void)
{
	if (git__pack_cache)
		return 0;

	git__on_shutdown(git_mwindow_files_free);

	return git_strmap_alloc(&git__pack_cache);
}
