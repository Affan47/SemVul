mif_read_data_field(const MIFImageHeader *image_header,
                    const MIFBlock *block,
                    const guchar *buffer,
                    gsize size,
                    GError **error)
{
    gint xres = image_header->setup.xres;
    gint yres = image_header->setup.yres;
    gdouble xreal = image_header->setup.xreal;
    gdouble yreal = image_header->setup.yreal;
    gdouble xoff = image_header->setup.xoff;
    gdouble yoff = image_header->setup.yoff;
    gdouble q = image_header->configuration.scan_int_to_meter;
    GwyDataField *dfield;
    gdouble *data;
    const gint16 *d16;
    gint i, j;

    if (err_DIMENSION(error, xres) || err_DIMENSION(error, yres))
        return NULL;

    if (!block->size || block->offset > size || block->size > size
        || block->offset + block->size > size) {
        g_set_error(error, GWY_MODULE_FILE_ERROR, GWY_MODULE_FILE_ERROR_DATA,
                    _("Image data are outside the file."));
        return NULL;
    }

    if (err_SIZE_MISMATCH(error, xres*yres*sizeof(gint16), block->size, FALSE))
        return NULL;

    dfield = gwy_data_field_new(xres, yres, xreal, yreal, FALSE);
    gwy_data_field_set_xoffset(dfield, xoff);
    gwy_data_field_set_yoffset(dfield, yoff);
    data = gwy_data_field_get_data(dfield);
    d16 = (const gint16*)(buffer + block->offset);

    gwy_si_unit_set_from_string(gwy_data_field_get_si_unit_xy(dfield), "m");
    gwy_si_unit_set_from_string(gwy_data_field_get_si_unit_z(dfield), "m");


    q *= 1.0e4;
    for (i = 0; i < yres; i++) {
        for (j = 0; j < yres; j++) {
            data[(yres-1 - i)*xres + j] = q*GINT16_FROM_LE(d16[i*xres + j]);
        }
    }

    return dfield;
}
