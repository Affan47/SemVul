vertical_expose (GdkEventExpose* ev)
{
	gint top_of_meter;
	GdkRectangle intersection;
	GdkRectangle background;

	top_of_meter = (gint) floor (pixheight * current_level);


	pixrect.height = top_of_meter;
	pixrect.y = pixheight - top_of_meter;

	background.x = 0;
	background.y = 0;
	background.width = pixrect.width;
	background.height = pixheight - top_of_meter;

	if (gdk_rectangle_intersect (&background, &ev->area, &intersection)) {
		get_window()->draw_rectangle (get_style()->get_black_gc(), true,
					      intersection.x, intersection.y,
					      intersection.width, intersection.height);
	}

	if (gdk_rectangle_intersect (&pixrect, &ev->area, &intersection)) {

		get_window()->draw_pixbuf(get_style()->get_fg_gc(get_state()), pixbuf,
					  intersection.x, intersection.y,
					  intersection.x, intersection.y,
					  intersection.width, intersection.height,
					  Gdk::RGB_DITHER_NONE, 0, 0);
	}


	if (hold_state) {
		last_peak_rect.x = 0;
		last_peak_rect.width = pixwidth;
		last_peak_rect.y = pixheight - (gint) floor (pixheight * current_peak);
		last_peak_rect.height = min(3, pixheight - last_peak_rect.y);

		get_window()->draw_pixbuf (get_style()->get_fg_gc(get_state()), pixbuf,
					   0, last_peak_rect.y,
					   0, last_peak_rect.y,
					   pixwidth, last_peak_rect.height,
					   Gdk::RGB_DITHER_NONE, 0, 0);
	} else {
		last_peak_rect.width = 0;
		last_peak_rect.height = 0;
	}

	return TRUE;
}
