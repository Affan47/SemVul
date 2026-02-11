_midgard_query_property_instance_init (GTypeInstance *instance, gpointer g_class)
{
	MidgardQueryProperty *self = (MidgardQueryProperty *)instance;

	self->priv = g_new (MidgardQueryPropertyPrivate, 1);
	self->priv->storage = NULL;
	self->priv->klass = NULL;
	self->priv->is_valid = FALSE;
	GValue value = {0, };
	self->priv->value = value;
	g_value_init (&self->priv->value, G_TYPE_STRING);
}
