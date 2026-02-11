compute_group (Sheet const *sheet,
	       int start, int end, double usable,
	       ColRowInfo const *(get_info)(Sheet const *sheet, int const p))
{
	double size_pts = 1.;
	int idx, count = 0;

	for (idx = start; idx <= end; idx++, count++) {
		ColRowInfo const *info = (*get_info) (sheet, idx);
		if (info->visible) {
			size_pts += info->size_pts;
			if (size_pts > usable)
				break;
		}
	}


	if (count ==0) {
		g_warning (_("Even one cell is too large for this page."));


		return 1;
	}

	return count;
}
