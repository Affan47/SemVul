totem_skipto_dispose (GObject *object)
{
	TotemSkipto *skipto;

	skipto = TOTEM_SKIPTO (object);
	if (skipto->priv && skipto->priv->xml != NULL) {
		g_object_unref (skipto->priv->xml);
		skipto->priv->xml = NULL;
	}

	G_OBJECT_CLASS (totem_skipto_parent_class)->dispose (object);
}
