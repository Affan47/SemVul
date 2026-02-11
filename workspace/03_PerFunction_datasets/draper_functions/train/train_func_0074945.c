evg_565_fill_const_a(s32 y, s32 count, EVG_Span *spans, EVGSurface *surf)
{
	u8 *dst = surf->pixels + y * surf->pitch_y;
	u32 col = surf->fill_col;
	register u32 a, fin, col_no_a;
	register s32 i;

	a = (col>>24)&0xFF;
	col_no_a = col&0x00FFFFFF;
	for (i=0; i<count; i++) {
		fin = mul255(a, spans[i].coverage);
		fin = (fin<<24) | col_no_a;
		overmask_565_const_run(fin, (u16*) (dst + spans[i].x * surf->pitch_x), surf->pitch_x, spans[i].len);
	}
}
