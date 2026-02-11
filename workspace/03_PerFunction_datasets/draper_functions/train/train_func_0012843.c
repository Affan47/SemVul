mx_list_view_set_property (GObject      *object,
                           guint         property_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  switch (property_id)
    {
    case PROP_MODEL:
      mx_list_view_set_model ((MxListView*) object,
                              (ClutterModel*) g_value_get_object (value));
      break;
    case PROP_ITEM_TYPE:
      mx_list_view_set_item_type ((MxListView*) object,
                                  g_value_get_gtype (value));
      break;
    case PROP_FACTORY:
      mx_list_view_set_factory ((MxListView*) object,
                                (MxItemFactory*) g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
