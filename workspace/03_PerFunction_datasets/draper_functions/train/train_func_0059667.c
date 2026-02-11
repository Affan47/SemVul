hawki_distortion_apply_maps
(cpl_imagelist   *   ilist,
 cpl_image       **  dist_x,
 cpl_image       **  dist_y)
{
    cpl_image       *   corr[HAWKI_NB_DETECTORS] ;
    int                 i, j ;


    if (ilist == NULL) return -1 ;
    if (dist_x == NULL) return -1 ;
    if (dist_y == NULL) return -1 ;


    for (i=0 ; i<HAWKI_NB_DETECTORS ; i++)
    {
        cpl_image * cur_image;


        cur_image = cpl_imagelist_get(ilist, i);


        corr[i] = hawki_distortion_correct_detector(cur_image,dist_x[i],dist_y[i]);
        if(corr[i] == NULL)
        {
            cpl_msg_error(__func__, "Cannot correct the distortion") ;
            for (j=0 ; j<i ; j++) cpl_image_delete(corr[j]) ;
            return -1 ;
        }
    }


    for (i=0 ; i<HAWKI_NB_DETECTORS ; i++)
        cpl_imagelist_set(ilist, corr[i], i);


    return 0 ;
}
