gtk_xtext_buffer_show(GtkXText * xtext, xtext_buffer * buf, int render)
{
	int w, h;

	buf->xtext = xtext;

	if (xtext->buffer == buf)
		return;


	if (xtext->add_io_tag) {
		g_source_remove(xtext->add_io_tag);
		xtext->add_io_tag = 0;
	}

	if (xtext->io_tag) {
		g_source_remove(xtext->io_tag);
		xtext->io_tag = 0;
	}

	if (!GTK_WIDGET_REALIZED(GTK_WIDGET(xtext)))
		gtk_widget_realize(GTK_WIDGET(xtext));

	gdk_drawable_get_size(GTK_WIDGET(xtext)->window, &w, &h);


	if (buf->needs_recalc) {
		buf->needs_recalc = FALSE;
		gtk_xtext_recalc_widths(buf, TRUE);
	}


	xtext->buffer = buf;
	dontscroll(buf);
	xtext->adj->value = buf->old_value;
	xtext->adj->upper = buf->num_lines;
	if (xtext->adj->upper == 0) {
		xtext->adj->upper = 1;

	} else if (xtext->adj->value > xtext->adj->upper - xtext->adj->page_size) {

		xtext->adj->value = xtext->adj->upper - xtext->adj->page_size;
		if (xtext->adj->value < 0)
			xtext->adj->value = 0;
	}

	if (render) {

		if (buf->window_width != w) {
			buf->window_width = w;
			gtk_xtext_calc_lines(buf, FALSE);
			if (buf->scrollbar_down)
				gtk_adjustment_set_value(xtext->adj, xtext->adj->upper -
							 xtext->adj->page_size);
		} else if (buf->window_height != h) {
			buf->window_height = h;
			buf->pagetop_ent = NULL;
			gtk_xtext_adjustment_set(buf, FALSE);
		}

		gtk_xtext_render_page(xtext);
		gtk_adjustment_changed(xtext->adj);
	} else {

		xtext->avoid_trans = TRUE;
	}
}
