fit_scrbar(ScrBarWidget w)
{
    if (w->scrbar.slider_position < 0)
	w->scrbar.slider_position = 0;
    else if (w->scrbar.allow_off) {
	if (w->scrbar.slider_position >= w->scrbar.canvas_length) {
	    if (w->scrbar.canvas_length == 0)
		w->scrbar.slider_position = 0;
	    else
		w->scrbar.slider_position = w->scrbar.canvas_length - 1;
	}
    } else if (w->scrbar.slider_position + w->scrbar.slider_length >
	       w->scrbar.canvas_length) {
	w->scrbar.slider_position = w->scrbar.canvas_length -
	    w->scrbar.slider_length;
	if (w->scrbar.slider_position < 0)
	    w->scrbar.slider_position = 0;
    }
}
