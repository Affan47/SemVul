gwy_app_update_data_range_type(GwyDataView *data_view,
                               gint id)
{
    GtkWidget *data_window, *widget;
    GwyPixmapLayer *layer;
    GwyColorAxis *color_axis;
    GwyContainer *data;
    GwyTicksStyle ticks_style;
    gboolean show_labels;
    gchar key[40];

    data_window = gtk_widget_get_ancestor(GTK_WIDGET(data_view),
                                          GWY_TYPE_DATA_WINDOW);
    if (!data_window) {
        g_warning("GwyDataView has no GwyDataWindow ancestor");
        return;
    }

    widget = gwy_data_window_get_color_axis(GWY_DATA_WINDOW(data_window));
    color_axis = GWY_COLOR_AXIS(widget);
    data = gwy_data_view_get_data(data_view);

    g_snprintf(key, sizeof(key), "/%d/show", id);

    if (gwy_container_contains_by_name(data, key)) {
        ticks_style = GWY_TICKS_STYLE_CENTER;
        show_labels = FALSE;
    }
    else {
        layer = gwy_data_view_get_base_layer(data_view);
        switch (gwy_layer_basic_get_range_type(GWY_LAYER_BASIC(layer))) {
            case GWY_LAYER_BASIC_RANGE_FULL:
            case GWY_LAYER_BASIC_RANGE_FIXED:
            case GWY_LAYER_BASIC_RANGE_AUTO:
            ticks_style = GWY_TICKS_STYLE_AUTO;
            show_labels = TRUE;
            break;

            case GWY_LAYER_BASIC_RANGE_ADAPT:
            ticks_style = GWY_TICKS_STYLE_NONE;
            show_labels = TRUE;
            break;

            default:
            g_warning("Unknown range type");
            ticks_style = GWY_TICKS_STYLE_NONE;
            show_labels = FALSE;
            break;
        }
    }

    gwy_color_axis_set_ticks_style(color_axis, ticks_style);
    gwy_color_axis_set_labels_visible(color_axis, show_labels);
}
