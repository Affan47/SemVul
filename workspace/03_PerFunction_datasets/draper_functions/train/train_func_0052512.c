g_vfs_backend_set_property (GObject         *object,
			    guint            prop_id,
			    const GValue    *value,
			    GParamSpec      *pspec)
{
  GVfsBackend *backend = G_VFS_BACKEND (object);

  switch (prop_id)
    {
    case PROP_OBJECT_PATH:
      backend->priv->object_path = g_value_dup_string (value);
      break;
    case PROP_DAEMON:
      backend->priv->daemon = G_VFS_DAEMON (g_value_dup_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
