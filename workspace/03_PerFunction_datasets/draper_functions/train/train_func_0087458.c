udisks_linux_block_object_get_property (GObject    *__object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
  UDisksLinuxBlockObject *object = UDISKS_LINUX_BLOCK_OBJECT (__object);

  switch (prop_id)
    {
    case PROP_DAEMON:
      g_value_set_object (value, udisks_linux_block_object_get_daemon (object));
      break;

    case PROP_DEVICE:
      g_value_set_object (value, udisks_linux_block_object_get_device (object));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
