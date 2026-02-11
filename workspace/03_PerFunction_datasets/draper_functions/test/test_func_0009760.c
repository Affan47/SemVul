render_chart_margin_spacers(GkrellmChart *cp)
	{
	GkrellmMargin	*m;
	GkrellmSpacer	*ts, *bs;

	ts = &cp->top_spacer;
	bs = &cp->bottom_spacer;
	if (ts->image)
		gtk_container_remove(GTK_CONTAINER(ts->vbox), ts->image);
	if (bs->image)
		gtk_container_remove(GTK_CONTAINER(bs->vbox), bs->image);
	ts->image = bs->image = NULL;
	m = gkrellm_get_style_margins(cp->style);
	ts->piximage = cp->bg_piximage;
	ts->height   = m->top;
	bs->piximage = cp->bg_piximage;
	bs->height   = m->bottom;

	if (!gkrellm_render_spacer(ts, 0, m->top,
				_GK.frame_left_chart_overlap, _GK.frame_right_chart_overlap))
		gtk_widget_hide(ts->vbox);

	if (!gkrellm_render_spacer(bs,
				gdk_pixbuf_get_height(cp->bg_piximage->pixbuf) - m->bottom,
				m->bottom,
				_GK.frame_left_chart_overlap, _GK.frame_right_chart_overlap))
		gtk_widget_hide(bs->vbox);
	}
