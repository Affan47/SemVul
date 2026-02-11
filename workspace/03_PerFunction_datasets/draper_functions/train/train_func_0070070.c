draw_set_info(set_info_t *si, int refresh)
{
	SDL_Rect ir = {270, 50, 320, 250+ch};
	int x, y;
	char buf[64];


	stk_surface_blit(ssd.background,ir.x,ir.y,ir.w,ir.h,
							stk_display,ir.x,ir.y);
	if (si == NULL) {
		stk_display_store_rect( &ir );
		stk_display_update( STK_UPDATE_RECTS );
		return;
	}


	stk_surface_blit(si->thumbnail,0,0,si->thumbnail->w,si->thumbnail->h,
				stk_display, ir.x, ir.y);


	x = ir.x + si->thumbnail->w / 2; y = ir.y + si->thumbnail->h + 2;
	ssd.standard_font->align = STK_FONT_ALIGN_CENTER_X | STK_FONT_ALIGN_TOP;
	snprintf(buf, 64, _("by %s, %d levels"), si->author, si->num_levels);
	stk_font_write(ssd.standard_font, stk_display, x, y, STK_OPAQUE, buf);
	x = ir.x + si->thumbnail->w / 2; y = ir.y + si->thumbnail->h - 40;
	ssd.caption_font->align = STK_FONT_ALIGN_CENTER_X | STK_FONT_ALIGN_TOP;
	snprintf(buf, 64, _("%s v%d.%02d"), si->name, si->version.major,
							si->version.minor);
	stk_font_write(ssd.caption_font, stk_display, x, y, STK_OPAQUE, buf);


	chart_show_compact(chart_set_query(si->name),
					ir.x + (ir.w-cw)/2, ir.y + 264, cw, ch);

	if (refresh) {
		stk_display_store_rect( &ir );
		stk_display_update( STK_UPDATE_RECTS );
	}
}
