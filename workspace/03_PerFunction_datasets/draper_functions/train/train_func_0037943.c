on_scl_song_change_value (GtkRange* range, GtkScrollType* scroll, gdouble value, GbemolApp* app)
{
	gchar* str;
	gint t;

	app->priv->update_scl_song = FALSE;

	t = (gint) (gbemol_mpd_get_total_time (app->mpd) * value);
	if (t < 0)
		return FALSE;

	str = g_markup_printf_escaped ("%02d:%02d", t / 60, t % 60);
	gtk_label_set_markup (GTK_LABEL (app->priv->lbl_time), str);
	g_free (str);

	gbemol_mpd_seek (app->mpd, gbemol_mpd_get_current_id (app->mpd), t);

	app->priv->update_scl_song = TRUE;

	return FALSE;
}
