git_mwindow_file_deregister(git_mwindow_file *mwf)
{
	git_mwindow_ctl *ctl = &mem_ctl;
	git_mwindow_file *cur;
	unsigned int i;

	git_mutex_lock(&git__mwindow_mutex);
	git_vector_foreach(&ctl->windowfiles, i, cur) {
		if (cur == mwf) {
			git_vector_remove(&ctl->windowfiles, i);
			git_mutex_unlock(&git__mwindow_mutex);
			return 0;
		}
	}
	git_mutex_unlock(&git__mwindow_mutex);

	giterr_set(GITERR_ODB, "Failed to find the memory window file to deregister");
	return -1;
}
