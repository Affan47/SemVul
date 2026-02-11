gdk_pixbuf_loader_close (GdkPixbufLoader *loader,
                         GError         **error)
{
        GdkPixbufLoaderPrivate *priv;
        gboolean retval = TRUE;

        g_return_val_if_fail (GDK_IS_PIXBUF_LOADER (loader), TRUE);
        g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

        priv = loader->priv;

        if (priv->closed)
                return TRUE;


        if (priv->image_module == NULL)
                {
                        GError *tmp = NULL;
                        gdk_pixbuf_loader_load_module (loader, NULL, &tmp);
                        if (tmp != NULL)
                                {
                                        g_propagate_error (error, tmp);
                                        retval = FALSE;
                                }
                }

        if (priv->image_module && priv->image_module->stop_load && priv->context)
                {
                        GError *tmp = NULL;
                        if (!priv->image_module->stop_load (priv->context, &tmp) || tmp)
                                {


					if (tmp) {
						if (error && *error == NULL)
							g_propagate_error (error, tmp);
						else
							g_error_free (tmp);
					}
                                        retval = FALSE;
                                }
                }

        priv->closed = TRUE;

        if (priv->needs_scale)
                {

                        g_signal_emit (loader, pixbuf_loader_signals[AREA_PREPARED], 0);
                        g_signal_emit (loader, pixbuf_loader_signals[AREA_UPDATED], 0,
                                       0, 0, priv->width, priv->height);
                }


        g_signal_emit (loader, pixbuf_loader_signals[CLOSED], 0);

        return retval;
}
