i_datafield_to_largefield(GwyDataField *datafield,
                          GwyDataField *tipfield,
                          gdouble min,
                          gdouble step)
{
    gint **ret;
    gint col, row;
    gint xres, yres, xnew, ynew;
    gint txr2, tyr2;
    gint minimum;
    gdouble *data;

    minimum = (gint)((gwy_data_field_get_min(datafield) - min)/step);
    xres = datafield->xres;
    yres = datafield->yres;
    xnew = xres + tipfield->xres;
    ynew = yres + tipfield->yres;
    txr2 = tipfield->xres/2;
    tyr2 = tipfield->yres/2;

    data = datafield->data;
    ret = _gwy_morph_lib_iallocmatrix(ynew, xnew);
    for (row = 0; row < ynew; row++) {
        for (col = 0; col < xnew; col++) {
            if (col >= txr2
                && col < xres + txr2
                && row >= tyr2
                && row < yres + tyr2)
                ret[row][col] = (gint)(((data[col - txr2 + xres*(row - tyr2)])
                                        - min) /step);
            else
                ret[row][col] = minimum;
        }
    }

    return ret;
}
