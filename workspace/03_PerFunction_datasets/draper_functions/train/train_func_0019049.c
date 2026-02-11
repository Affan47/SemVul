interpolate_field(guint npoints,
                  const GwyTriangulationPointXYZ *points,
                  GwyDataField *dfield)
{
    gdouble xoff, yoff, qx, qy;
    guint xres, yres, i, j, k;
    gdouble *d;

    xres = gwy_data_field_get_xres(dfield);
    yres = gwy_data_field_get_yres(dfield);
    xoff = gwy_data_field_get_xoffset(dfield);
    yoff = gwy_data_field_get_yoffset(dfield);
    qx = gwy_data_field_get_xreal(dfield)/xres;
    qy = gwy_data_field_get_yreal(dfield)/yres;
    d = gwy_data_field_get_data(dfield);

    for (i = 0; i < yres; i++) {
        gdouble y = yoff + qy*(i + 0.5);

        for (j = 0; j < xres; j++) {
            gdouble x = xoff + qx*(j + 0.5);
            gdouble w = 0.0;
            gdouble s = 0.0;

            for (k = 0; k < npoints; k++) {
                const GwyTriangulationPointXYZ *pt = points + k;
                gdouble dx = x - pt->x;
                gdouble dy = y - pt->y;
                gdouble r2 = dx*dx + dy*dy;

                r2 *= r2;
                if (G_UNLIKELY(r2 == 0.0)) {
                    s = pt->z;
                    w = 1.0;
                    break;
                }

                r2 = 1.0/r2;
                w += r2;
                s += r2*pt->z;
            }
            *(d++) = s/w;
        }
    }
}
