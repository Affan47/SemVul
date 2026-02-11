pseudo_laplace_average(GwyDataField *dfield,
                       gint ximin, gint yimin,
                       gint ximax, gint yimax)
{
    gdouble *data, *disttable;
    gint i, j, k, rowstride, width, height;

    gwy_debug("pseudo_laplace: (%d,%d) x (%d,%d)", ximin, ximax, yimin, yimax);
    data = gwy_data_field_get_data(dfield);
    rowstride = gwy_data_field_get_xres(dfield);


    width = ximax - ximin + 1;
    height = yimax - yimin + 1;
    disttable = g_new(gdouble, width*height);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++)
            disttable[i*width + j] = 1.0/(i*i + j*j + 1e-16);
    }

    for (i = yimin; i < yimax; i++) {
        for (j = ximin; j < ximax; j++) {
            gdouble w = 0.0, s = 0.0;

            for (k = yimin-1; k < yimax+1; k++) {
                gdouble ww;

                ww = disttable[ABS(k - i)*width + j-ximin+1];
                w += ww;
                s += ww*data[k*rowstride + ximin-1];

                ww = disttable[ABS(k - i)*width + ximax-j];
                w += ww;
                s += ww*data[k*rowstride + ximax];
            }

            for (k = ximin-1; k < ximax+1; k++) {
                gdouble ww;

                ww = disttable[ABS(i-yimin+1)*width + ABS(k - j)];
                w += ww;
                s += ww*data[(yimin-1)*rowstride + k];

                ww = disttable[ABS(yimax - i)*width + ABS(k - j)];
                w += ww;
                s += ww*data[yimax*rowstride + k];
            }

            data[i*rowstride + j] = s/w;
        }
    }

    g_free(disttable);
}
