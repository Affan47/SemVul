tp_room_list_get_property (GObject *object,
    guint property_id,
    GValue *value,
    GParamSpec *pspec)
{
  TpRoomList *self = (TpRoomList *) object;

  switch (property_id)
    {
      case PROP_ACCOUNT:
        g_value_set_object (value, tp_room_list_get_account (self));
        break;

      case PROP_SERVER:
        g_value_set_string (value, tp_room_list_get_server (self));
        break;

      case PROP_LISTING:
        g_value_set_boolean (value, self->priv->listing);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}
