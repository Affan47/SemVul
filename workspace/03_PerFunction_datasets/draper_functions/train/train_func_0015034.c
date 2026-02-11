window_update_canvases(void)
{
	window *wind;

	for (wind = FirstWindow; wind != NULL; wind = wind->next)
		gr_init_sub_bitmap (&wind->w_canv.cv_bitmap,
							wind->w_canv.cv_bitmap.bm_parent,
							wind->w_canv.cv_bitmap.bm_x,
							wind->w_canv.cv_bitmap.bm_y,
							wind->w_canv.cv_bitmap.bm_w,
							wind->w_canv.cv_bitmap.bm_h);
}
