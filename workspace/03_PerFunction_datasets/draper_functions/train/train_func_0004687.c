totem_fullscreen_dispose (GObject *object)
{
        TotemFullscreenPrivate *priv = TOTEM_FULLSCREEN_GET_PRIVATE (object);

	if (priv->xml != NULL) {
		g_object_unref (priv->xml);
		priv->xml = NULL;
		gtk_widget_destroy (priv->exit_popup);
		gtk_widget_destroy (priv->control_popup);
	}

	G_OBJECT_CLASS (totem_fullscreen_parent_class)->dispose (object);
}
