gm_text_scroller_update_text_buffer(GmTextScroller *scroller) {
	if (scroller->priv->text_buffer != NULL) {
		g_signal_handlers_disconnect_by_func(scroller->priv->text_buffer,
				G_CALLBACK(on_gm_text_scroller_text_buffer_changed),
				scroller);

		g_object_unref(scroller->priv->text_buffer);
	}

	scroller->priv->text_buffer =
			gtk_text_view_get_buffer(scroller->priv->text_view);

	if (scroller->priv->text_buffer != NULL) {
		g_object_ref(scroller->priv->text_buffer);

		g_signal_connect(scroller->priv->text_buffer, "changed",
				G_CALLBACK(on_gm_text_scroller_text_buffer_changed), scroller);
	}

}
