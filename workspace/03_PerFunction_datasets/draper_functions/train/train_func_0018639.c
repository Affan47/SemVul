tp_base_contact_list_channel_set_property (GObject *object,
    guint property_id,
    const GValue *value,
    GParamSpec *pspec)
{
  TpBaseContactListChannel *self = TP_BASE_CONTACT_LIST_CHANNEL (object);

  switch (property_id)
    {
    case PROP_MANAGER:
      g_assert (self->manager == NULL);
      self->manager = g_value_dup_object (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}
