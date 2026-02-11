gwy_data_view_finalize(GObject *object)
{
    GwyDataView *data_view;

    g_return_if_fail(GWY_IS_DATA_VIEW(object));

    data_view = GWY_DATA_VIEW(object);
    gwy_object_unref(data_view->base_layer);
    gwy_object_unref(data_view->alpha_layer);
    gwy_object_unref(data_view->top_layer);
    gwy_object_unref(data_view->data);

    G_OBJECT_CLASS(gwy_data_view_parent_class)->finalize(object);
}
