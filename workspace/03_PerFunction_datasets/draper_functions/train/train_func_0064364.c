e_map_finalize (GObject *object)
{
	EMap *map;

	map = E_MAP (object);

	while (map->priv->tweens)
		e_map_tween_destroy (map, map->priv->tweens->data);
	e_map_stop_tweening (map);

	if (map->priv->map_pixbuf) {
		g_object_unref (map->priv->map_pixbuf);
		map->priv->map_pixbuf = NULL;
	}


	g_assert (map->priv->map_render_surface == NULL);

	G_OBJECT_CLASS (e_map_parent_class)->finalize (object);
}
