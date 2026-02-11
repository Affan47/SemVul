guestfs_rsync_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
  GuestfsRsync *self = GUESTFS_RSYNC(object);
  GuestfsRsyncPrivate *priv = self->priv;

  switch (property_id) {
    case PROP_GUESTFS_RSYNC_ARCHIVE:
      priv->archive = g_value_get_enum (value);
      break;

    case PROP_GUESTFS_RSYNC_DELETEDEST:
      priv->deletedest = g_value_get_enum (value);
      break;

    default:

      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
  }
}
