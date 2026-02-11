on_parser_parse_stream_returned (GObject *source,
                                 GAsyncResult *result,
                                 gpointer user_data)
{
	GcrViewerWidget *self = GCR_VIEWER_WIDGET (user_data);
	GError *error = NULL;
	GcrRenderer *renderer;

	gcr_parser_parse_stream_finish (self->pv->parser, result, &error);

	if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED) ||
	    g_error_matches (error, GCR_DATA_ERROR, GCR_ERROR_CANCELLED)) {
		viewer_stop_loading_files (self);

	} else if (g_error_matches (error, GCR_DATA_ERROR, GCR_ERROR_LOCKED)) {


	} else if (error) {
		renderer = gcr_failure_renderer_new (self->pv->display_name, error);
		gcr_viewer_add_renderer (self->pv->viewer, renderer);
		g_object_unref (renderer);
		g_error_free (error);
	}

	viewer_load_next_file (self);
}
