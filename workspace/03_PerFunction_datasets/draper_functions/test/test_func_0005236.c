git_diff_patch_line_stats(
	size_t *total_ctxt,
	size_t *total_adds,
	size_t *total_dels,
	const git_diff_patch *patch)
{
	size_t totals[3], idx;

	memset(totals, 0, sizeof(totals));

	for (idx = 0; idx < patch->lines_size; ++idx) {
		switch (patch->lines[idx].origin) {
		case GIT_DIFF_LINE_CONTEXT:  totals[0]++; break;
		case GIT_DIFF_LINE_ADDITION: totals[1]++; break;
		case GIT_DIFF_LINE_DELETION: totals[2]++; break;
		default:


			break;
		}
	}

	if (total_ctxt)
		*total_ctxt = totals[0];
	if (total_adds)
		*total_adds = totals[1];
	if (total_dels)
		*total_dels = totals[2];

	return 0;
}
