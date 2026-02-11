new_window(git_mwindow_file *mwf, git_file fd, size_t size, off_t offset)
{
	size_t walign = ctl.window_size / 2;
	size_t len;
	git_mwindow *w;

	w = git__malloc(sizeof(*w));
	if (w == NULL)
		return w;

	memset(w, 0x0, sizeof(*w));
	w->offset = (offset / walign) * walign;

	len = size - w->offset;
	if (len > ctl.window_size)
		len = ctl.window_size;

	ctl.mapped += len;

	while(ctl.mapped_limit < ctl.mapped &&
	      git_mwindow_close_lru(mwf) == GIT_SUCCESS) {}


	if (git_futils_mmap_ro(&w->window_map, fd, w->offset, len) < GIT_SUCCESS)
		goto cleanup;

	ctl.mmap_calls++;
	ctl.open_windows++;

	if (ctl.mapped > ctl.peak_mapped)
		ctl.peak_mapped = ctl.mapped;

	if (ctl.open_windows > ctl.peak_open_windows)
		ctl.peak_open_windows = ctl.open_windows;

	return w;

cleanup:
	free(w);
	return NULL;
}
