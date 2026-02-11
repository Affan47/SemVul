irplib_wlxcorr_signal_resample(
        cpl_vector          *   resampled,
        const cpl_vector    *   xbounds,
        const cpl_bivector  *   hires)
{
    const int           hrsize = cpl_bivector_get_size(hires);
    const cpl_vector*   xhires ;
    const cpl_vector*   yhires ;
    const double    *   pxhires ;
    const double    *   pyhires ;
    const double    *   pxbounds ;
    cpl_vector      *   ybounds ;
    cpl_bivector    *   boundary ;
    double          *   pybounds ;
    double          *   presampled ;
    int                 nsamples ;
    int                 i, itt ;


    if ((!resampled) || (!xbounds) || (!hires)) return -1 ;


    nsamples = cpl_vector_get_size(resampled) ;


    presampled = cpl_vector_get_data(resampled) ;
    pxbounds = cpl_vector_get_data_const(xbounds) ;
    xhires = cpl_bivector_get_x_const(hires) ;
    yhires = cpl_bivector_get_y_const(hires) ;
    pxhires = cpl_vector_get_data_const(xhires) ;
    pyhires = cpl_vector_get_data_const(yhires) ;


    ybounds = cpl_vector_new(cpl_vector_get_size(xbounds)) ;
    boundary = cpl_bivector_wrap_vectors((cpl_vector*)xbounds,ybounds) ;
    pybounds = cpl_vector_get_data(ybounds) ;


    if (cpl_bivector_get_size(boundary) != nsamples + 1) {
        cpl_bivector_unwrap_vectors(boundary) ;
        cpl_vector_delete(ybounds) ;
        return -1 ;
    }


    itt = cpl_vector_find(xhires, pxbounds[0]);


    if (cpl_bivector_interpolate_linear(boundary, hires)) {
        cpl_bivector_unwrap_vectors(boundary) ;
        cpl_vector_delete(ybounds) ;
        return -1 ;
    }


    while (pxhires[itt] < pxbounds[0]) itt++;

    for (i=0; i < nsamples; i++) {


        double xlow  = pxbounds[i];
        double x     = pxhires[itt];

        if (x > pxbounds[i+1]) x = pxbounds[i+1];


        presampled[i] = pybounds[i] * (x - xlow);


        while ((pxhires[itt] < pxbounds[i+1]) && (itt < hrsize)) {
            const double xprev = x;
            x = pxhires[itt+1];
            if (x > pxbounds[i+1]) x = pxbounds[i+1];
            presampled[i] += pyhires[itt] * (x - xlow);
            xlow = xprev;
            itt++;
        }


        presampled[i] += pybounds[i+1] * (pxbounds[i+1] - xlow);


        presampled[i] /= 2 * (pxbounds[i+1] - pxbounds[i]);
    }
    cpl_bivector_unwrap_vectors(boundary) ;
    cpl_vector_delete(ybounds) ;
    return 0 ;
}
