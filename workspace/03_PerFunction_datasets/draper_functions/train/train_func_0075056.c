SetScreenVisible(void)
{
	if (VIDEOMODE_src_offset_left < 24)
		Screen_visible_x1 = 24;
	else
		Screen_visible_x1 = VIDEOMODE_src_offset_left;
	if (VIDEOMODE_src_offset_left + VIDEOMODE_src_width > 360)
		Screen_visible_x2 = 360;
	else
		Screen_visible_x2 = VIDEOMODE_src_offset_left + VIDEOMODE_src_width;
	Screen_visible_y1 = VIDEOMODE_src_offset_top;
	Screen_visible_y2 = VIDEOMODE_src_offset_top + VIDEOMODE_src_height;
}
