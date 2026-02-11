sc_seam_diff_hrest(const long int vfirst, const long int vlast) {
	const int hfirst = sm_cols * sm_threads + (sm_cols == 0);

	if (hfirst >= sm_hlast) return;

   	for (int i = vfirst; i < vlast; i++)
	   	diff_ln(&diff_img, &intn_img, i, hfirst, sm_hlast);
}
