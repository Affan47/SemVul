init_gcs(ScrListWidget w)
{
    XGCValues	values;

    values.foreground = w->scrlist.foreground_pixel;
    values.background = w->core.background_pixel;
    values.font = w->scrlist.font->fid;
    w->scrlist.default_gc =
	XtGetGC((Widget)w, GCForeground | GCBackground | GCFont, &values);
    values.background = w->scrlist.highlight_pixel;
    w->scrlist.selected_gc =
	XtGetGC((Widget)w, GCForeground | GCBackground, &values);
    if (w->shadow.line_mode)
	w->scrlist.highlight_gc = (GC)0;
    else {
	values.foreground = w->scrlist.highlight_pixel;
	w->scrlist.highlight_gc = XtGetGC((Widget)w, GCForeground, &values);
    }
}
