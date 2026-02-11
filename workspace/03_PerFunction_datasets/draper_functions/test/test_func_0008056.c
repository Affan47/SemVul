hawki_detectors_labelise
(const cpl_frameset * in)
{
    int             *   labels ;
    cpl_bivector    *   offsets ;
    int                 nframes ;
    double          *   poff_x ;
    double          *   poff_y ;
    double              off_x_mean;
    double              off_y_mean;
    int                 i ;


    if (in == NULL) return NULL ;


    nframes = cpl_frameset_get_size(in) ;


    if ((offsets = hawki_get_header_tel_offsets((cpl_frameset *)in)) == NULL) {
        cpl_msg_error(__func__, "Cannot read the offsets") ;
        return NULL ;
    }
    poff_x = cpl_bivector_get_x_data(offsets) ;
    poff_y = cpl_bivector_get_y_data(offsets) ;


    off_x_mean = cpl_vector_get_mean(cpl_bivector_get_x(offsets));
    off_y_mean = cpl_vector_get_mean(cpl_bivector_get_y(offsets));


    labels = cpl_malloc(nframes * sizeof(int)) ;
    for (i=0 ; i<nframes ; i++) {
        if (poff_x[i] - off_x_mean <= 0 && poff_y[i] - off_y_mean <= 0)
            labels[i] = 1 ;
        else if (poff_x[i] - off_x_mean >= 0 && poff_y[i] - off_y_mean <= 0)
            labels[i] = 2 ;
        else if (poff_x[i] - off_x_mean >= 0 && poff_y[i] - off_y_mean >= 0)
            labels[i] = 3 ;
        else if (poff_x[i] - off_x_mean <= 0 && poff_y[i] - off_y_mean >= 0)
            labels[i] = 4 ;
        else labels[i] = 0 ;
    }
    cpl_bivector_delete(offsets) ;
    return labels ;
}
