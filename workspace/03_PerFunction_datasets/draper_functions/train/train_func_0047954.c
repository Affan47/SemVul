indicator_menu_item_set_property (GObject      *object,
                                  guint         property_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
    switch (property_id)
    {
        case PROP_ICON:
            indicator_menu_item_set_icon (INDICATOR_MENU_ITEM (object),
                                          g_value_get_object (value));
            break;

        case PROP_ICON_NAME:
            indicator_menu_item_set_icon_name (INDICATOR_MENU_ITEM (object),
                                               g_value_get_string (value));
            break;

        case PROP_LABEL:
            indicator_menu_item_set_label (INDICATOR_MENU_ITEM (object),
                                           g_value_get_string (value));
            break;

        case PROP_RIGHT:
            indicator_menu_item_set_right (INDICATOR_MENU_ITEM (object),
                                           g_value_get_string (value));
            break;

        case PROP_RIGHT_IS_LOZENGE:
            indicator_menu_item_set_right_is_lozenge (INDICATOR_MENU_ITEM (object),
                                                      g_value_get_boolean (value));
            break;


        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
