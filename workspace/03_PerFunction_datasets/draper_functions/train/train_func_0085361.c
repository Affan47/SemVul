tp_room_list_set_property (GObject *object,
    guint property_id,
    const GValue *value,
    GParamSpec *pspec)
{
  TpRoomList *self = (TpRoomList *) object;

  switch (property_id)
    {
      case PROP_ACCOUNT:
        g_assert (self->priv->account == NULL);
        self->priv->account = g_value_dup_object (value);
        break;

      case PROP_SERVER:
        g_assert (self->priv->server == NULL);
        self->priv->server = g_value_dup_string (value);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}
