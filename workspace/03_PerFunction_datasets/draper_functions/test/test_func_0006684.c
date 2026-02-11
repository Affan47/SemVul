gcr_failure_renderer_render (GcrRenderer *renderer,
                             GcrViewer *viewer)
{
	GcrFailureRenderer *self = GCR_FAILURE_RENDERER (renderer);
	GcrDisplayView *view;
	gchar *display;
	GIcon *icon;

	if (GCR_IS_DISPLAY_VIEW (viewer)) {
		view = GCR_DISPLAY_VIEW (viewer);

	} else {
		g_warning ("GcrFailureRenderer only works with internal specific "
		           "GcrViewer returned by gcr_viewer_new().");
		return;
	}

	_gcr_display_view_begin (view, renderer);

	if (g_error_matches (self->pv->error, GCR_DATA_ERROR, GCR_ERROR_UNRECOGNIZED))
		icon = g_themed_icon_new ("dialog-warning");
	else
		icon = g_themed_icon_new ("dialog-error");
	_gcr_display_view_set_icon (view, renderer, icon);
	g_object_unref (icon);

	_gcr_display_view_append_title (view, renderer, self->pv->label);

	if (self->pv->label)
		display = g_strdup_printf (_("Could not display '%s'"), self->pv->label);
	else
		display = g_strdup (_("Could not display file"));
	_gcr_display_view_append_content (view, renderer, display, NULL);
	g_free (display);

	if (self->pv->error->message)
		_gcr_display_view_append_value (view, renderer, _("Reason"),
		                                self->pv->error->message, FALSE);

	_gcr_display_view_end (view, renderer);
}
