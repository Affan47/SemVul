photos_application_dispose (GObject *object)
{
  PhotosApplication *self = PHOTOS_APPLICATION (object);
  PhotosApplicationPrivate *priv = self->priv;

  if (priv->miners_running != NULL)
    {
      photos_application_stop_miners (self);
      g_list_free_full (priv->miners_running, g_object_unref);
      priv->miners_running = NULL;
    }

  if (priv->resource != NULL)
    {
      g_resources_unregister (priv->resource);
      g_resource_unref (priv->resource);
      priv->resource = NULL;
    }

  g_clear_object (&priv->settings);
  g_clear_object (&priv->fs_action);
  g_clear_object (&priv->gear_action);
  g_clear_object (&priv->open_action);
  g_clear_object (&priv->print_action);
  g_clear_object (&priv->properties_action);
  g_clear_object (&priv->sel_all_action);
  g_clear_object (&priv->sel_none_action);
  g_clear_object (&priv->set_bg_action);
  g_clear_object (&priv->flickr_miner);
  g_clear_object (&priv->item_mngr);
  g_clear_object (&priv->src_mngr);
  g_clear_object (&priv->camera_cache);
  g_clear_object (&priv->mode_cntrlr);

  G_OBJECT_CLASS (photos_application_parent_class)->dispose (object);
}
