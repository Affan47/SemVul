gm_text_scroller_finalize(GObject *object) {
	GmTextScroller *obj = GM_TEXT_SCROLLER(object);

	if (obj->priv->text_buffer != NULL) {
		g_signal_handlers_disconnect_by_func(obj->priv->text_buffer,
				G_CALLBACK(on_gm_text_scroller_text_buffer_changed),
				obj);

		g_object_unref(obj->priv->text_buffer);
	}

	if (obj->priv->idle_handler) {
		g_source_remove(obj->priv->idle_handler);
	}

	g_signal_handlers_disconnect_by_func(obj->priv->text_view,
			G_CALLBACK(on_gm_text_scroller_text_view_notify), obj);
	g_signal_handlers_disconnect_by_func(obj->priv->text_view,
			G_CALLBACK(on_gm_text_scroller_text_view_style_set), obj);
	g_signal_handlers_disconnect_by_func(obj->priv->text_view,
			G_CALLBACK(on_gm_text_scroller_text_view_destroy), obj);

	G_OBJECT_CLASS(gm_text_scroller_parent_class)->finalize(object);
}
