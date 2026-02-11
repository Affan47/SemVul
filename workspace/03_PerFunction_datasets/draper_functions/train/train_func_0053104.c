_midgard_blob_instance_init(
		 GTypeInstance *instance, gpointer g_class)
{
	MidgardBlob *self = (MidgardBlob *) instance;
	self->priv = g_new(MidgardBlobPrivate, 1);

	self->priv->attachment = NULL;
	self->priv->location = NULL;
	self->priv->blobdir = NULL;
	self->priv->filepath = NULL;
	self->priv->channel = NULL;
	self->priv->encoding = NULL;
	self->priv->content = NULL;
	self->priv->parentguid = NULL;
}
