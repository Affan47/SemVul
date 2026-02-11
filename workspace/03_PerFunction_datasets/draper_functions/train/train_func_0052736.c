hf_render_info_new (void)
{
	HFRenderInfo *hfi;

	hfi = g_new0 (HFRenderInfo, 1);
	hfi->date_conv = go_date_conv_from_str ("Lotus:1900");
	hfi->date_time = value_new_float
		(go_date_timet_to_serial_raw (time (NULL), hfi->date_conv));

	range_init (&hfi->page_area, 0, 0, G_MAXINT / 2, G_MAXINT / 2);
	hfi->top_repeating.col = 0;
	hfi->top_repeating.row = 0;

	return hfi;
}
