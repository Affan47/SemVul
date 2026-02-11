renderer_free (Renderer *renderer)
{
	g_signal_handler_disconnect (renderer->renderer,
	                             renderer->queue_draw_handler);

	g_signal_handler_disconnect (renderer->renderer,
	                             renderer->size_changed_handler);

	g_signal_handler_disconnect (renderer->renderer,
	                             renderer->notify_xpad_handler);

	g_signal_handler_disconnect (renderer->renderer,
	                             renderer->notify_ypad_handler);

	g_signal_handler_disconnect (renderer->renderer,
	                             renderer->notify_visible_handler);

	_gtk_source_gutter_renderer_set_view (renderer->renderer,
	                                      NULL,
	                                      GTK_TEXT_WINDOW_PRIVATE);

	g_object_unref (renderer->renderer);
	g_slice_free (Renderer, renderer);
}
