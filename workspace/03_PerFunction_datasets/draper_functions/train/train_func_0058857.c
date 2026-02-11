indicator_menu_item_get_property (GObject    *object,
                                  guint       property_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
    IndicatorMenuItem *self = INDICATOR_MENU_ITEM (object);

    switch (property_id)
    {
        case PROP_ICON:
            g_value_set_object (value, indicator_menu_item_get_icon (self));
            break;

        case PROP_ICON_NAME:
            g_value_set_string (value, indicator_menu_item_get_icon_name (self));
            break;

        case PROP_LABEL:
            g_value_set_string (value, gtk_label_get_label (GTK_LABEL (self->priv->label)));
            break;

        case PROP_RIGHT:
            g_value_set_string (value, gtk_label_get_label (GTK_LABEL (self->priv->right_label)));
            break;

        case PROP_RIGHT_IS_LOZENGE:
            g_value_set_boolean (value, self->priv->right_is_lozenge);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
