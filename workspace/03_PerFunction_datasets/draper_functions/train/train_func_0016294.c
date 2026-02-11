view_constructed (GObject *object)
{
	GiggleViewPriv *priv = GET_PRIV (object);

	g_signal_connect (priv->action, "notify::visible",
			  G_CALLBACK (notify_visible_cb), object);

	if (G_OBJECT_CLASS (giggle_view_parent_class)->constructed)
		G_OBJECT_CLASS (giggle_view_parent_class)->constructed (object);
}
