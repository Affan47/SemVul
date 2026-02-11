glade_placeholder_get_property (GObject *object,
                                guint prop_id,
                                GValue *value,
                                GParamSpec *pspec)
{
  switch (prop_id)
    {
      case PROP_HADJUSTMENT:
      case PROP_VADJUSTMENT:
        g_value_set_object (value, NULL);
        break;
      case PROP_HSCROLL_POLICY:
      case PROP_VSCROLL_POLICY:
        g_value_set_enum (value, GTK_SCROLL_MINIMUM);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}
