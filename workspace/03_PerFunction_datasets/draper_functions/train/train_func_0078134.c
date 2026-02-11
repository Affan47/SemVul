redraw(void)
{
    alert_timeout = tvzero;
    alert_pos = 0;
    alert_len = 0;
    if (visual) {
	top_margin = bottom_margin = -1;
        clr();
    } else {
        bufputnc('\n', lines);
    }
    setup_screen();

    if (virtscreen) {
	hide_screen(display_screen);
	unhide_screen(display_screen);
    }
    return redraw_window(display_screen, 1);
}
