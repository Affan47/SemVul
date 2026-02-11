gwy_data_field_area_filter_sobel(GwyDataField *data_field,
                                 GwyOrientation orientation,
                                 gint col, gint row,
                                 gint width, gint height)
{
    static const gdouble hsobel[] = {
        0.25, 0, -0.25,
        0.5,  0, -0.5,
        0.25, 0, -0.25,
    };
    static const gdouble vsobel[] = {
         0.25,  0.5,  0.25,
         0,     0,    0,
        -0.25, -0.5, -0.25,
    };

    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    if (orientation == GWY_ORIENTATION_HORIZONTAL)
        gwy_data_field_area_convolve_3x3(data_field, hsobel,
                                         col, row, width, height);
    else
        gwy_data_field_area_convolve_3x3(data_field, vsobel,
                                         col, row, width, height);
}
