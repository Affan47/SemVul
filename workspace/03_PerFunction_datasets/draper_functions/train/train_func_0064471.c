create_pyramide(GwyDataField *tip, gdouble alpha, gint n, gdouble theta)
{
    gint col, row;
    gdouble rcol, rrow;
    gdouble scol, srow;
    gdouble ccol, crow;
    gdouble phi, phic;
    gdouble vm, radius;
    gdouble height;
    gdouble nangle;
    gdouble ca, sa, ir;
    gdouble add;

    if (n == 3)
        add = G_PI/6;
    else
        add = G_PI/4;

    add += theta;
    radius = sqrt((tip->xres/2)*(tip->xres/2)+(tip->yres/2)*(tip->yres/2));
    nangle = G_PI/n;
    height = gwy_data_field_itor(tip, radius)*cos(nangle)/tan(alpha);

    scol = tip->xres/2;
    srow = tip->yres/2;

    ca = cos(add);
    sa = sin(add);
    ir = 1.0/(radius*cos(G_PI/n));
    for (col = 0; col < tip->xres; col++) {
        for (row = 0; row < tip->yres; row++) {
            ccol = col - scol;
            crow = row - srow;
            rcol = -ccol*ca + crow*sa;
            rrow = ccol*sa + crow*ca;
            phi = atan2(rrow, rcol) + G_PI;
            phic = floor(phi/(2*G_PI/n))*2*G_PI/n + G_PI/n;
            vm = rcol*cos(phic) + rrow*sin(phic);
            tip->data[col + tip->xres*row] = height*(1 + vm*ir);
        }
    }

    gwy_data_field_invalidate(tip);
}
