gwy_data_window_size_allocate(GtkWidget *widget,
                              GtkAllocation *alc)
{
    gdouble excess, offset, pos, real;
    GwyDataWindow *data_window;
    GwyDataView *data_view;
    GwyContainer *data;
    GwyDataField *dfield;
    const gchar *k;

    data_window = GWY_DATA_WINDOW(widget);
    if (alc) {
        if (data_window->old_allocation.x == alc->x
            && data_window->old_allocation.y == alc->y
            && data_window->old_allocation.width == alc->width
            && data_window->old_allocation.height == alc->height)
            return;

        GTK_WIDGET_CLASS(gwy_data_window_parent_class)->size_allocate(widget,
                                                                      alc);
        data_window->old_allocation = *alc;
    }

    data_view = GWY_DATA_VIEW(data_window->data_view);
    g_return_if_fail(GWY_IS_DATA_VIEW(data_view));
    data = gwy_data_view_get_data(data_view);
    g_return_if_fail(GWY_IS_CONTAINER(data));

    k = gwy_pixmap_layer_get_data_key(gwy_data_view_get_base_layer(data_view));
    dfield = GWY_DATA_FIELD(gwy_container_get_object_by_name(data, k));
    g_return_if_fail(dfield);


    real =  gwy_data_field_get_xreal(dfield);
    offset = gwy_data_field_get_xoffset(dfield);
    excess = real * gwy_data_view_get_hexcess(data_view)/2.0;
    gwy_ruler_get_range(GWY_RULER(data_window->hruler),
                        NULL, NULL, &pos, NULL);
    gwy_ruler_set_range(GWY_RULER(data_window->hruler),
                        offset - excess, real + offset + excess, pos, real);


    real = gwy_data_field_get_yreal(dfield);
    offset = gwy_data_field_get_yoffset(dfield);
    excess = real * gwy_data_view_get_vexcess(data_view)/2.0;
    gwy_ruler_get_range(GWY_RULER(data_window->vruler),
                        NULL, NULL, &pos, NULL);
    gwy_ruler_set_range(GWY_RULER(data_window->vruler),
                        offset - excess, real + offset + excess, pos, real);

    gwy_data_window_update_title(data_window);
}
