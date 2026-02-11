interrupt(int sig)
{
	char response;
	char progress[PATH_MAX];

	if (!last_reported_block || last_reported_block == last_fs_block)
		sprintf(progress, _("progress unknown.\n"));
	else
		sprintf(progress, _("processing block %llu out of %llu\n"),
			(unsigned long long)last_reported_block,
			(unsigned long long)last_fs_block);

	response = generic_interrupt("gfs2_fsck", pass, progress,
				     _("Do you want to abort gfs2_fsck, skip " \
				     "the rest of this pass or continue " \
				     "(a/s/c)?"), "asc");
	if (tolower(response) == 's') {
		skip_this_pass = TRUE;
		return;
	}
	else if (tolower(response) == 'a') {
		fsck_abort = TRUE;
		return;
	}
}
