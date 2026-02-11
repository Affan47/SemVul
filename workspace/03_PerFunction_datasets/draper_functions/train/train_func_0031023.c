branch_open(struct view *view)
{
	const char *branch_log[] = {
		"git", "log", "--no-color", "--pretty=raw",
			"--simplify-by-decoration", "--all", NULL
	};

	if (!start_update(view, branch_log, NULL)) {
		report("Failed to load branch data");
		return TRUE;
	}

	setup_update(view, view->id);
	branch_open_visitor(view, &branch_all);
	foreach_ref(branch_open_visitor, view);
	view->p_restore = TRUE;

	return TRUE;
}
