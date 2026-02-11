hawki_bkg_imglist_calib
(cpl_imagelist *       ilist,
 cpl_imagelist *       bkg)
{
    int                 idet;


    if (ilist == NULL) return -1 ;


    if (bkg != NULL)
    {
        cpl_msg_info(cpl_func, "Subtract the images by the bkg") ;

        for(idet = 0; idet < HAWKI_NB_DETECTORS ; ++idet)
        {
            if (cpl_image_subtract(cpl_imagelist_get(ilist, idet),
                                   cpl_imagelist_get(bkg, idet))!=CPL_ERROR_NONE)
            {
                cpl_msg_error(cpl_func,"Cannot apply the bkg to the images");
                return -1 ;
            }
        }
    }


    return 0 ;

}
