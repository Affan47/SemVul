wt_status_print(struct wt_status *s)
{
	unsigned char sha1[20];
	const char *branch_color = color(WT_STATUS_HEADER);

	s->is_initial = get_sha1(s->reference, sha1) ? 1 : 0;
	if (s->branch) {
		const char *on_what = "On branch ";
		const char *branch_name = s->branch;
		if (!prefixcmp(branch_name, "refs/heads/"))
			branch_name += 11;
		else if (!strcmp(branch_name, "HEAD")) {
			branch_name = "";
			branch_color = color(WT_STATUS_NOBRANCH);
			on_what = "Not currently on any branch.";
		}
		color_fprintf(s->fp, color(WT_STATUS_HEADER), "# ");
		color_fprintf_ln(s->fp, branch_color, "%s%s", on_what, branch_name);
		if (!s->is_initial)
			wt_status_print_tracking(s);
	}

	if (s->is_initial) {
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER), "#");
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER), "# Initial commit");
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER), "#");
		wt_status_print_initial(s);
	}
	else {
		wt_status_print_updated(s);
	}

	wt_status_print_changed(s);
	if (wt_status_submodule_summary)
		wt_status_print_submodule_summary(s);
	if (show_untracked_files)
		wt_status_print_untracked(s);
	else if (s->commitable)
		 fprintf(s->fp, "# Untracked files not listed (use -u option to show untracked files)\n");

	if (s->verbose && !s->is_initial)
		wt_status_print_verbose(s);
	if (!s->commitable) {
		if (s->amend)
			fprintf(s->fp, "# No changes\n");
		else if (s->nowarn)
			;
		else if (s->workdir_dirty)
			printf("no changes added to commit (use \"git add\" and/or \"git commit -a\")\n");
		else if (s->workdir_untracked)
			printf("nothing added to commit but untracked files present (use \"git add\" to track)\n");
		else if (s->is_initial)
			printf("nothing to commit (create/copy files and use \"git add\" to track)\n");
		else if (!show_untracked_files)
			printf("nothing to commit (use -u to show untracked files)\n");
		else
			printf("nothing to commit (working directory clean)\n");
	}
}
