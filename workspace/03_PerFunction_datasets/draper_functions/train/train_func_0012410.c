handle_unlimit_command(String *args, int offset)
{
    Screen *screen = display_screen;

    if (!screen_has_filter(screen))
	return shareval(val_zero);
    clear_screen_filter(screen);
    if (!screen->paused)
	screen_end(0);
    redraw_window(screen, 0);
    update_status_field(NULL, STAT_MORE);
    return shareval(val_one);
}
