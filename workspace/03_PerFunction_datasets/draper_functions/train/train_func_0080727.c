gwy_data_field_set_column(GwyDataField *data_field,
                          GwyDataLine* data_line,
                          gint col)
{
    gint k;
    gdouble *p;

    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    g_return_if_fail(GWY_IS_DATA_LINE(data_line));
    g_return_if_fail(col >= 0 && col < data_field->xres);
    g_return_if_fail(data_field->yres == data_line->res);

    p = data_field->data + col;
    for (k = 0; k < data_field->yres; k++)
        p[k*data_field->xres] = data_line->data[k];
    gwy_data_field_invalidate(data_field);
}
