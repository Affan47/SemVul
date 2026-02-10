screen_end(int need_redraw)
{
    Screen *screen = display_screen;
    int oldmore = more;

    hide_screen(screen);
    if (screen->nback_filtered) {
	screen->nback_filtered = screen->nback = 0;
	screen->nnew_filtered = screen->nnew = 0;
	special_var[VAR_more].val.u.ival = 0;


	need_redraw = 1;
	screen->maxbot = screen->bot = screen->pline.tail;
	screen_refilter(screen);

	special_var[VAR_more].val.u.ival = oldmore;
    }

    screen->paused = 0;
    reset_outcount(screen);
    if (need_redraw) {
	redraw_window(screen, 0);
	if (visual) {
	    update_status_field(NULL, STAT_MORE);
	} else {
	    prompt = fgprompt();
	}
    }
    return 1;
}
