status_open(struct view *view)
{
	reset_view(view);

	add_line_data(view, NULL, LINE_STAT_HEAD);
	status_update_onbranch();

	io_run_bg(update_index_argv);

	if (is_initial_commit()) {
		if (!status_run(view, status_list_no_head_argv, 'A', LINE_STAT_STAGED))
			return FALSE;
	} else if (!status_run(view, status_diff_index_argv, 0, LINE_STAT_STAGED)) {
		return FALSE;
	}

	if (!status_run(view, status_diff_files_argv, 0, LINE_STAT_UNSTAGED) ||
	    !status_run(view, status_list_other_argv, '?', LINE_STAT_UNTRACKED))
		return FALSE;


	if (!view->p_restore)
		status_restore(view);
	return TRUE;
}
