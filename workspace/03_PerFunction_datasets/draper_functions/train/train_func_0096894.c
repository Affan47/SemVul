evg_user_fill_const(s32 y, s32 count, EVG_Span *spans, EVGSurface *surf)
{
	u32 col_no_a;
	s32 i;

	col_no_a = surf->fill_col;
	for (i=0; i<count; i++) {
		if (spans[i].coverage != 0xFF) {
			u32 a = mul255(0xFF, spans[i].coverage);
			surf->raster_fill_run_alpha(surf->raster_cbk, spans[i].x, y, spans[i].len, col_no_a, a);
		} else {
			surf->raster_fill_run_no_alpha(surf->raster_cbk, spans[i].x, y, spans[i].len, col_no_a);
		}
	}
}
