zpj_skydrive_entry_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
  ZpjSkydriveEntry *self = ZPJ_SKYDRIVE_ENTRY (object);
  ZpjSkydriveEntryPrivate *priv = self->priv;

  switch (prop_id)
    {
    case PROP_CREATED_TIME:
      g_value_set_boxed (value, priv->created_time);
      break;

    case PROP_DESCRIPTION:
      g_value_set_string (value, priv->description);
      break;

    case PROP_FROM_ID:
      g_value_set_string (value, priv->from_id);
      break;

    case PROP_FROM_NAME:
      g_value_set_string (value, priv->from_name);
      break;

    case PROP_ID:
      g_value_set_string (value, priv->id);
      break;

    case PROP_NAME:
      g_value_set_string (value, priv->name);
      break;

    case PROP_PARENT_ID:
      g_value_set_string (value, priv->parent_id);
      break;

    case PROP_TYPE:
      g_value_set_enum (value, priv->type);
      break;

    case PROP_UPDATED_TIME:
      g_value_set_boxed (value, priv->updated_time);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
