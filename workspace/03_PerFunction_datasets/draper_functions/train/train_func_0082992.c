sinfo_sky_background_estimate(cpl_vector *spectrum,
                                             int msize,
                                             int fsize)
{

    cpl_vector  * minf=NULL;
    cpl_vector  * maxf=NULL;
    cpl_vector  * smof=NULL;
    cpl_vector  * back=NULL;
    double* pb=NULL;
    double* ps=NULL;

    int     i=0;
    int length=0;


    cknull(spectrum,"null input data");

    if (msize % 2 == 0)
        msize++;

    if (fsize % 2 == 0)
        fsize++;
    check_nomsg(length=cpl_vector_get_size(spectrum));

    if (msize < 3 || fsize < msize || length < 2*fsize)
        return NULL;


    cknull_nomsg(minf = sinfo_filter_min(spectrum, msize));
    cknull_nomsg(smof = sinfo_filter_smo(minf, fsize));
    cpl_vector_delete(minf);
    cknull_nomsg(maxf = sinfo_filter_max(smof,2*msize+1));
    cpl_vector_delete(smof);
    cknull_nomsg(smof = sinfo_filter_smo(maxf, 2*fsize+1));
    cpl_vector_delete(maxf);
    cknull_nomsg(minf = sinfo_filter_min(smof, 2*msize+1));
    cpl_vector_delete(smof);
    cknull_nomsg(smof = sinfo_filter_smo(minf, 2*fsize+1));
    cpl_vector_delete(minf);
    cknull_nomsg(back=cpl_vector_new(length));
    cknull_nomsg(pb=cpl_vector_get_data(back));
    cknull_nomsg(ps=cpl_vector_get_data(smof));

    for (i = 0; i < length; i++) {
        pb[i] = ps[i];
     }
    cpl_vector_delete(smof);

    return back;
 cleanup:

    return NULL;

}
