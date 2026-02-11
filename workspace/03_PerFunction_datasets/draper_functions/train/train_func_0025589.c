hawki_cal_distortion_qc
(hawki_distortion ** distortion,
 int              *  nmatched_pairs,
 double           *  rms)
{
    int idet;
    cpl_propertylist ** qclists;


    qclists = cpl_malloc(HAWKI_NB_DETECTORS * sizeof(cpl_propertylist*)) ;


    for(idet = 0 ; idet < HAWKI_NB_DETECTORS ; ++idet)
    {

        qclists[idet] = cpl_propertylist_new() ;

        cpl_propertylist_append_double
            (qclists[idet], "ESO QC DIST NMATCHED", nmatched_pairs[idet]);

        cpl_propertylist_append_double
            (qclists[idet], "ESO QC DIST TOTAL RMS", rms[idet]);


    }

    return qclists;
}
