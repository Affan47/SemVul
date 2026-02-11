gwy_data_window_get_property(GObject*object,
                             guint prop_id,
                             GValue *value,
                             GParamSpec *pspec)
{
    GwyDataWindow *window = GWY_DATA_WINDOW(object);

    switch (prop_id) {
        case PROP_DATA_NAME:
        g_value_set_string(value, window->data_name->str);
        break;

        case PROP_UL_CORNER:
        g_value_set_object(value, window->ul_corner);
        break;

        case PROP_DATA_VIEW:
        g_value_set_object(value, window->data_view);
        break;

        case PROP_COLOR_AXIS:
        g_value_set_object(value, window->coloraxis);
        break;

        default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
