clock_map_init (ClockMap *this)
{
        int i;
        ClockMapPrivate *priv = PRIVATE (this);

        gtk_widget_set_has_window (GTK_WIDGET (this), FALSE);

	priv->last_refresh = 0;
	priv->width = 0;
	priv->height = 0;
	priv->highlight_timeout_id = 0;
        priv->stock_map_pixbuf = NULL;

        g_assert (sizeof (marker_files)/sizeof (char *) == MARKER_NB);

        for (i = 0; i < MARKER_NB; i++) {
                char *resource;

                resource = g_strconcat (CLOCK_RESOURCE_PATH "icons/", marker_files[i], NULL);
                priv->location_marker_pixbuf[i] = gdk_pixbuf_new_from_resource (resource, NULL);
                g_free (resource);
        }
}
