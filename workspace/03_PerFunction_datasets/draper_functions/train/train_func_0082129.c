gwy_data_field_crosscorrelate_init(GwyDataField *data_field1,
                                   GwyDataField *data_field2,
                                   GwyDataField *x_dist,
                                   GwyDataField *y_dist,
                                   GwyDataField *score,
                                   gint search_width,
                                   gint search_height,
                                   gint window_width,
                                   gint window_height)
{
    GwyCrossCorrelationState *state;

    g_return_val_if_fail(GWY_IS_DATA_FIELD(data_field1), NULL);
    g_return_val_if_fail(GWY_IS_DATA_FIELD(data_field2), NULL);
    g_return_val_if_fail(data_field1->xres == data_field2->xres
                     && data_field1->yres == data_field2->yres, NULL);
    g_return_val_if_fail(!x_dist || GWY_IS_DATA_FIELD(x_dist), NULL);
    g_return_val_if_fail(!y_dist || GWY_IS_DATA_FIELD(y_dist), NULL);
    g_return_val_if_fail(!score || GWY_IS_DATA_FIELD(score), NULL);

    state = g_new0(GwyCrossCorrelationState, 1);

    state->cs.state = GWY_COMPUTATION_STATE_INIT;
    state->cs.fraction = 0.0;
    state->data_field1 = g_object_ref(data_field1);
    state->data_field2 = g_object_ref(data_field2);

    if (x_dist)
        state->x_dist = g_object_ref(x_dist);
    if (y_dist)
        state->y_dist = g_object_ref(y_dist);
    if (score)
        state->score = g_object_ref(score);

    state->search_width = search_width;
    state->search_height = search_height;
    state->window_width = window_width;
    state->window_height = window_height;

    return (GwyComputationState*)state;
}
