git_xdiff_parse_hunk(git_diff_hunk *hunk, const char *header)
{

	if (*header != '@')
		goto fail;
	if (git_xdiff_scan_int(&header, &hunk->old_start) < 0)
		goto fail;
	if (*header == ',') {
		if (git_xdiff_scan_int(&header, &hunk->old_lines) < 0)
			goto fail;
	} else
		hunk->old_lines = 1;
	if (git_xdiff_scan_int(&header, &hunk->new_start) < 0)
		goto fail;
	if (*header == ',') {
		if (git_xdiff_scan_int(&header, &hunk->new_lines) < 0)
			goto fail;
	} else
		hunk->new_lines = 1;
	if (hunk->old_start < 0 || hunk->new_start < 0)
		goto fail;

	return 0;

fail:
	giterr_set(GITERR_INVALID, "Malformed hunk header from xdiff");
	return -1;
}
