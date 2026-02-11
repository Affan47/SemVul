photos_base_manager_dispose (GObject *object)
{
  PhotosBaseManager *self = PHOTOS_BASE_MANAGER (object);
  PhotosBaseManagerPrivate *priv = self->priv;

  if (priv->objects != NULL)
    {
      g_hash_table_unref (priv->objects);
      priv->objects = NULL;
    }

  g_clear_object (&priv->active_object);

  G_OBJECT_CLASS (photos_base_manager_parent_class)->dispose (object);
}
