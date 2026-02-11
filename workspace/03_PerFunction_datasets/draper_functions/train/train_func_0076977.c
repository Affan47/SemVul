gwy_data_field_area_clear(GwyDataField *data_field,
                          gint col, gint row, gint width, gint height)
{
    gint i;
    gdouble *drow;

    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    g_return_if_fail(col >= 0 && row >= 0
                     && width >= 0 && height >= 0
                     && col + width <= data_field->xres
                     && row + height <= data_field->yres);

    gwy_data_field_invalidate(data_field);
    if (height == 1 || (col == 0 && width == data_field->xres)) {
        memset(data_field->data + data_field->xres*row + col, 0,
               width*height*sizeof(gdouble));
        return;
    }

    for (i = 0; i < height; i++) {
        drow = data_field->data + (row + i)*data_field->xres + col;
        memset(drow, 0, width*sizeof(gdouble));
    }
}
