gwy_data_field_area_extract(GwyDataField *data_field,
                            gint col, gint row,
                            gint width, gint height)
{
    GwyDataField *result;
    gint i;

    g_return_val_if_fail(GWY_IS_DATA_FIELD(data_field), NULL);
    g_return_val_if_fail(col >= 0
                         && row >= 0
                         && width > 0
                         && height > 0
                         && col + width <= data_field->xres
                         && row + height <= data_field->yres,
                         NULL);

    if (col == 0
        && row == 0
        && width == data_field->xres
        && height == data_field->yres)
        return gwy_data_field_duplicate(data_field);

    result = gwy_data_field_new(width, height,
                                data_field->xreal*width/data_field->xres,
                                data_field->yreal*height/data_field->yres,
                                FALSE);
    for (i = 0; i < height; i++) {
        memcpy(result->data + i*width,
               data_field->data + (i + row)*data_field->xres + col,
               width*sizeof(gdouble));
    }
    if (data_field->si_unit_xy)
        result->si_unit_xy = gwy_si_unit_duplicate(data_field->si_unit_xy);
    if (data_field->si_unit_z)
        result->si_unit_z = gwy_si_unit_duplicate(data_field->si_unit_z);

    return result;
}
