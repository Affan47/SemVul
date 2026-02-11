irplib_strehl_disk_flux(const cpl_image * im,
                               double            xpos,
                               double            ypos,
                               double            rad,
                               double            bg)
{
    const double    sqr = rad * rad;
    double          sqrest;
    const float *   pim;
    double          flux = 0.0;
    double          yj, xi;
    int             nx, ny;
    int             lx, ly, ux, uy;
    int             i, j;


    cpl_ensure(im != NULL, CPL_ERROR_NULL_INPUT, 0.0);
    cpl_ensure(cpl_image_get_type(im) == CPL_TYPE_FLOAT,
               CPL_ERROR_UNSUPPORTED_MODE, 0.0);
    cpl_ensure(rad > 0.0, CPL_ERROR_ILLEGAL_INPUT, 0.0);

    nx = cpl_image_get_size_x(im);
    ny = cpl_image_get_size_y(im);


    lx = (int)(xpos - rad);
    ly = (int)(ypos - rad);
    if (lx < 0) lx = 0;
    if (ly < 0) ly = 0;


    ux = (int)(xpos + rad) + 1;
    uy = (int)(ypos + rad) + 1;
    if (ux > (nx-1)) ux = nx-1;
    if (uy > (ny-1)) uy = ny-1;

    pim = cpl_image_get_data_float_const(im);
    for (j=ly ; j<uy ; j++) {
        yj = (double)j - ypos;
        sqrest = sqr - yj * yj;
        for (i=lx; i<ux ; i++) {
            xi = (double)i - xpos;
            if (sqrest >= xi * xi && irplib_isnan(pim[i+j*nx]) == 0) {
                flux += (double)pim[i+j*nx] - bg;
            }
        }
    }
    return flux;
}
