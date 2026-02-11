mx_box_layout_child_get_property (GObject    *object,
                                  guint       property_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  MxBoxLayoutChild *child = MX_BOX_LAYOUT_CHILD (object);

  switch (property_id)
    {
    case PROP_EXPAND:
      g_value_set_boolean (value, child->expand);
      break;
    case PROP_X_FILL:
      g_value_set_boolean (value, child->x_fill);
      break;
    case PROP_Y_FILL:
      g_value_set_boolean (value, child->y_fill);
      break;
    case PROP_X_ALIGN:
      g_value_set_enum (value, child->x_align);
      break;
    case PROP_Y_ALIGN:
      g_value_set_enum (value, child->y_align);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
