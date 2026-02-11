totem_embedded_open_internal (TotemEmbedded *emb,
			      gboolean start_play,
			      GError **error)
{
	char *uri;


	if (emb->is_browser_stream) {
		if (emb->size > 0)
			uri = g_strdup_printf ("fd://0?size=%"G_GINT64_FORMAT, emb->size);
		else
			uri = g_strdup ("fd://0");
	} else {
		uri = g_strdup (emb->current_uri);
	}

	if (!uri) {
		g_set_error_literal (error,
                                     TOTEM_EMBEDDED_ERROR_QUARK,
                                     TOTEM_EMBEDDED_NO_URI,
                                     _("No URI to play"));


		return FALSE;
	}

	g_message ("totem_embedded_open_internal '%s' subtitle '%s' is-browser-stream %d start-play %d",
		   uri, emb->current_subtitle_uri, emb->is_browser_stream, start_play);

	bacon_video_widget_set_logo_mode (emb->bvw, FALSE);

	bacon_video_widget_open (emb->bvw, uri);
	bacon_video_widget_set_text_subtitle (emb->bvw, emb->current_subtitle_uri);
	g_free (uri);


	if (start_play)
		totem_embedded_play (emb, NULL);
	else
		totem_glow_button_set_glow (TOTEM_GLOW_BUTTON (emb->pp_button), TRUE);

	totem_embedded_update_menu (emb);
	if (emb->href_uri != NULL)
		totem_fullscreen_set_title (emb->fs, emb->href_uri);
	else
		totem_fullscreen_set_title (emb->fs, emb->current_uri);

	return TRUE;
}
