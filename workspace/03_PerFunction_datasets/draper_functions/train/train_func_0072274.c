__midgard_transaction_dispose (GObject *object)
{
	MidgardTransaction *self = MIDGARD_TRANSACTION (object);
	if (self->priv->mgd != NULL) {
		g_object_unref (self->priv->mgd);
		self->priv->mgd = NULL;
	}

	__parent_class->dispose (object);
}
