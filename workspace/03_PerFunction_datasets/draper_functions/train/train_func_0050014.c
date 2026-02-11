tp_text_channel_get_property (GObject *object,
    guint property_id,
    GValue *value,
    GParamSpec *pspec)
{
  TpTextChannel *self = (TpTextChannel *) object;

  switch (property_id)
    {
      case PROP_SUPPORTED_CONTENT_TYPES:
        g_value_set_boxed (value,
            tp_text_channel_get_supported_content_types (self));
        break;

      case PROP_MESSAGE_PART_SUPPORT_FLAGS:
        g_value_set_uint (value,
            tp_text_channel_get_message_part_support_flags (self));
        break;

      case PROP_DELIVERY_REPORTING_SUPPORT:
        g_value_set_uint (value,
            tp_text_channel_get_delivery_reporting_support (self));
        break;

      case PROP_MESSAGE_TYPES:
        g_value_set_boxed (value,
            tp_text_channel_get_message_types (self));
        break;

      case PROP_IS_SMS_CHANNEL:
        g_value_set_boolean (value, tp_text_channel_is_sms_channel (self));
        break;

      case PROP_SMS_FLASH:
        g_value_set_boolean (value, tp_text_channel_get_sms_flash (self));
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}
