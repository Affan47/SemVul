gbemol_app_set_cover_image(GbemolThreadData* data)
{
	GdkPixbuf *pix_img = NULL, *scaled;
	static GStaticMutex mutex = G_STATIC_MUTEX_INIT;

	gdk_threads_enter();
    g_static_mutex_lock (&mutex);

	pix_img = gbemol_utils_get_song_image(data->song);
	if (pix_img)
	{
		scaled = gdk_pixbuf_scale_simple (pix_img, 70, 70, GDK_INTERP_BILINEAR);
		gtk_image_set_from_pixbuf (GTK_IMAGE (data->app->priv->img_cover), scaled);
		g_object_unref(pix_img);
		g_object_unref(scaled);
		gtk_widget_show(data->app->priv->img_cover);
	}
	else
		gtk_widget_hide(data->app->priv->img_cover);

	gbemol_mpd_free_song(data->song);
	g_free(data);

	g_static_mutex_unlock (&mutex);
	gdk_threads_leave();

	return NULL;
}
