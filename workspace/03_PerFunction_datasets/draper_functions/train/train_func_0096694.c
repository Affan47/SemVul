e_map_finalize (GObject *object)
{
	EMap *view;
	EMapPrivate *priv;

	g_return_if_fail (object != NULL);
	g_return_if_fail (E_IS_MAP (object));

	view = E_MAP (object);
	priv = view->priv;

        while (priv->tweens)
                e_map_tween_destroy (view, priv->tweens->data);
        e_map_stop_tweening (view);

	if (priv->map_pixbuf)
	{
		g_object_unref (priv->map_pixbuf);
		priv->map_pixbuf = NULL;
	}


        g_assert (priv->map_render_surface == NULL);

	g_free (priv);
	view->priv = NULL;

	G_OBJECT_CLASS (e_map_parent_class)->finalize (object);
}
