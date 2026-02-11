check_font(void)
{
    if (local_font) {
	if (strcmp(local_font_desc, current_font_desc) != 0)
	    set_font(local_font_desc);
    } else if (global_font) {
	if (strcmp(global_font_desc, current_font_desc) != 0)
	    set_font(global_font_desc);
    } else if (strcmp(DEFAULT_FONT, current_font_desc) != 0)
	set_font(DEFAULT_FONT);
}
