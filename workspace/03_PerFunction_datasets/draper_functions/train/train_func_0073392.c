irplib_hist_init(irplib_hist   * hist,
                 unsigned long   nbins,
                 double          start,
                 double          range)
{

    cpl_ensure_code(hist         != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(nbins        >  0,    CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(range        >  0,    CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(hist -> bins == NULL, CPL_ERROR_ILLEGAL_INPUT);


    hist -> bins  = (unsigned long *) cpl_calloc(nbins, sizeof(unsigned long));
    hist -> nbins = nbins;
    hist -> start = start;
    hist -> range = range;

    return cpl_error_get_code();
}
