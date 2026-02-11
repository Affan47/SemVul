fpi_img_compare_print_data(struct fp_print_data *enrolled_print,
	struct fp_print_data *new_print)
{
	struct xyt_struct *gstruct = (struct xyt_struct *) enrolled_print->data;
	struct xyt_struct *pstruct = (struct xyt_struct *) new_print->data;
	GTimer *timer;
	int r;

	if (enrolled_print->type != PRINT_DATA_NBIS_MINUTIAE ||
			new_print->type != PRINT_DATA_NBIS_MINUTIAE) {
		fp_err("invalid print format");
		return -EINVAL;
	}

	timer = g_timer_new();
	r = bozorth_main(pstruct, gstruct);
	g_timer_stop(timer);
	fp_dbg("bozorth processing took %f seconds, score=%d",
		g_timer_elapsed(timer, NULL), r);
	g_timer_destroy(timer);

	return r;
}
