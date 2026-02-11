bonobo_dock_item_set_property (GObject            *object,
			      guint               param_id,
			      const GValue       *value,
			      GParamSpec         *pspec)
{
  BonoboDockItem *dock_item;

  g_return_if_fail (object != NULL);
  g_return_if_fail (BONOBO_IS_DOCK_ITEM (object));

  dock_item = BONOBO_DOCK_ITEM (object);

  switch (param_id)
    {
    case PROP_SHADOW:
      bonobo_dock_item_set_shadow_type (dock_item, g_value_get_enum (value));
      break;
    case PROP_ORIENTATION:
      bonobo_dock_item_set_orientation (dock_item, g_value_get_enum (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}
