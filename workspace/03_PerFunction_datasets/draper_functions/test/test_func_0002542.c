sc_seam_paral_accu(const int part) {
	const bool start = (part == 0),
				 end = (part >= parts);
	int vfirst = part * sm_lines,
		 vlast = end? sm_vlast: vfirst + sm_lines;

	sc_seam_diff_hrest(vfirst + start, vlast);

	vfirst -= !start;
	vlast  -= !end;

	if (info.flags.mark)
		for (int i = vfirst; i < vlast; i++) {
			mark_ln(&diff_img, &mark_img, i, 0, info.width);
			accu_ln(&diff_img, i, sm_hlast);
		}
	else
		for (int i = vfirst; i < vlast; i++)
			accu_ln(&diff_img, i, sm_hlast);

	return (parts == part);
}
