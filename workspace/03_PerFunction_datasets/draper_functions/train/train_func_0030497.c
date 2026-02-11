mask_process(GwyDataField *maskfield,
             GwyDataLine *drift)
{
    gint i, j, k, step, pos, xres, yres, w, from, to;
    gdouble *mdata, *rdata;

    gwy_data_field_clear(maskfield);
    xres = gwy_data_field_get_xres(maskfield);
    yres = gwy_data_field_get_yres(maskfield);

    step = xres/10;
    w = (xres + 3*PREVIEW_SIZE/4)/PREVIEW_SIZE;
    w = MAX(w, 1);
    rdata = gwy_data_line_get_data(drift);
    mdata = gwy_data_field_get_data(maskfield);
    for (i = 0; i < yres; i++) {
        for (j = -2*step - step/2; j <= xres + 2*step + step/2; j += step) {
            pos = j + GWY_ROUND(gwy_data_line_rtoi(drift, rdata[i]));
            from = MAX(0, pos - w/2);
            to = MIN(pos + (w - w/2) - 1, xres-1);
            for (k = from; k <= to; k++)
                mdata[i*xres + k] = 1.0;
        }
    }
    gwy_data_field_data_changed(maskfield);
}
