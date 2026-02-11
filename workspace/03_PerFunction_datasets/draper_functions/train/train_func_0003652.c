page_scroll(Widget    gw,
			XEvent   *event,
			String   *params,
			Cardinal *no_params)
{
    ScrBarWidget	w = (ScrBarWidget)gw;
    float		amount;

    if (w->scrbar.mode != ScrBarModeNone ||
	*no_params != 1 || sscanf(params[0], "%f", &amount) != 1) {
	XBell(XtDisplay(w), 0);
	return;
    }

    w->scrbar.slider_position += amount * (float)w->scrbar.slider_length;
    fit_scrbar(w);
    calc_scrbar_coords(w);
    draw_thumb(w, NULL);
    send_scroll_report(w);
}
