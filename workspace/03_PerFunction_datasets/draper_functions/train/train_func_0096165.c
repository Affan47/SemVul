branch_open(struct view *view)
{
	const char *branch_log[] = {
		"git", "log", "--no-color", "--pretty=raw",
			"--simplify-by-decoration", "--all", NULL
	};

	if (!run_io_rd(&view->io, branch_log, NULL, FORMAT_NONE)) {
		report("Failed to load branch data");
		return TRUE;
	}

	setup_update(view, view->id);
	foreach_ref(branch_open_visitor, view);
	view->p_restore = TRUE;

	return TRUE;
}
