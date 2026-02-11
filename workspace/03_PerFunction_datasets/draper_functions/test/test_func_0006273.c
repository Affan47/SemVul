facet_view_recompute(GtkAdjustment *adj,
                     FacetsControls *controls)
{
    GwyVectorLayer *layer;
    GwyDataField *dfield;
    GwySelection *selection;
    const gchar *key;

    controls->args->kernel_size = gwy_adjustment_get_int(adj);
    gwy_app_wait_cursor_start(GTK_WINDOW(controls->dialog));
    dfield = gwy_container_get_object_by_name(controls->mydata, "/0/data");
    gwy_data_field_facet_distribution(dfield, 2*controls->args->kernel_size + 1,
                                      controls->fdata);


    if (gwy_container_gis_object_by_name(controls->mydata, "/0/mask",
                                         &dfield)) {
        gwy_data_field_clear(dfield);
        gwy_data_field_data_changed(dfield);
    }

    layer = gwy_data_view_get_top_layer(GWY_DATA_VIEW(controls->fview));
    key = gwy_vector_layer_get_selection_key(layer);
    selection = gwy_container_get_object_by_name(controls->fdata, key);
    gwy_selection_clear(selection);
    gwy_app_wait_cursor_finish(GTK_WINDOW(controls->dialog));
    facets_invalidate(controls);
}
