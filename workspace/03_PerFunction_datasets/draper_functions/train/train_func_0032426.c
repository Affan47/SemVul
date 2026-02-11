gwy_data_field_area_filter_kuwahara(GwyDataField *data_field,
                                    gint col, gint row,
                                    gint width, gint height)
{
    gint i, j, x, y, ctr;
    gdouble *buffer, *kernel;

    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    g_return_if_fail(col >= 0 && row >= 0
                     && width > 0 && height > 0
                     && col + width <= data_field->xres
                     && row + height <= data_field->yres);

    buffer = g_new(gdouble, width*height);
    kernel = g_new(gdouble, 25);


    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {

            ctr = 0;
            for (y = -2; y <= 2; y++) {
                for (x = -2; x <= 2; x++)
                    kernel[ctr++] = gwy_data_field_get_val_closest(data_field,
                                                                   col + j + x,
                                                                   row + i + y);
            }
            buffer[i*width + j] = kuwahara_block(kernel);
        }
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++)
            data_field->data[col + j + data_field->xres * (row + i)]
                                                  = buffer[i*width + j];
    }

    g_free(kernel);
    g_free(buffer);
}
