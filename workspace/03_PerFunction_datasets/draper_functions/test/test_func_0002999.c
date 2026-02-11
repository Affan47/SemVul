wt_status_print(struct wt_status *s)
{
	const char *branch_color = color(WT_STATUS_HEADER, s);

	if (s->branch) {
		const char *on_what = "On branch ";
		const char *branch_name = s->branch;
		if (!prefixcmp(branch_name, "refs/heads/"))
			branch_name += 11;
		else if (!strcmp(branch_name, "HEAD")) {
			branch_name = "";
			branch_color = color(WT_STATUS_NOBRANCH, s);
			on_what = "Not currently on any branch.";
		}
		color_fprintf(s->fp, color(WT_STATUS_HEADER, s), "# ");
		color_fprintf_ln(s->fp, branch_color, "%s%s", on_what, branch_name);
		if (!s->is_initial)
			wt_status_print_tracking(s);
	}

	if (s->is_initial) {
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER, s), "#");
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER, s), "# Initial commit");
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER, s), "#");
	}

	wt_status_print_updated(s);
	wt_status_print_unmerged(s);
	wt_status_print_changed(s);
	if (s->submodule_summary &&
	    (!s->ignore_submodule_arg ||
	     strcmp(s->ignore_submodule_arg, "all"))) {
		wt_status_print_submodule_summary(s, 0);
		wt_status_print_submodule_summary(s, 1);
	}
	if (s->show_untracked_files) {
		wt_status_print_other(s, &s->untracked, "Untracked", "add");
		if (s->show_ignored_files)
			wt_status_print_other(s, &s->ignored, "Ignored", "add -f");
	} else if (s->commitable)
		fprintf(s->fp, "# Untracked files not listed%s\n",
			advice_status_hints
			? " (use -u option to show untracked files)" : "");

	if (s->verbose)
		wt_status_print_verbose(s);
	if (!s->commitable) {
		if (s->amend)
			fprintf(s->fp, "# No changes\n");
		else if (s->nowarn)
			;
		else if (s->workdir_dirty)
			printf("no changes added to commit%s\n",
				advice_status_hints
				? " (use \"git add\" and/or \"git commit -a\")" : "");
		else if (s->untracked.nr)
			printf("nothing added to commit but untracked files present%s\n",
				advice_status_hints
				? " (use \"git add\" to track)" : "");
		else if (s->is_initial)
			printf("nothing to commit%s\n", advice_status_hints
				? " (create/copy files and use \"git add\" to track)" : "");
		else if (!s->show_untracked_files)
			printf("nothing to commit%s\n", advice_status_hints
				? " (use -u to show untracked files)" : "");
		else
			printf("nothing to commit%s\n", advice_status_hints
				? " (working directory clean)" : "");
	}
}
