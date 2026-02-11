sinfo_new_mult_image_by_mask (cpl_image * im,cpl_image * mask )
{
    cpl_image * reImage=NULL ;
    int        i=0 ;
    int ix=0;
    int iy=0;
    int mx=0;
    int my=0;


    float* pmdata=NULL;
    float* podata=NULL;

    if ( NULL == im )
    {
        sinfo_msg_error("no input image given!") ;
        return NULL ;
    }
    if ( NULL == mask )
    {
        sinfo_msg_error("no mask image given!") ;
        return NULL ;
    }
    ix=cpl_image_get_size_x(im);
    iy=cpl_image_get_size_y(im);
    mx=cpl_image_get_size_x(mask);
    my=cpl_image_get_size_y(mask);

    if ( ix != mx || iy != my)
    {
        sinfo_msg_error("image sizes are not correspondent!") ;
        return NULL ;
    }

    reImage = cpl_image_duplicate( im ) ;
    podata=cpl_image_get_data_float(reImage);
    pmdata=cpl_image_get_data_float(mask);

    for ( i = 0 ; i < (int) ix*iy ; i ++ )
    {
        if ( pmdata[i] == 0. )
        {
            podata[i] = ZERO ;
        }
    }

    return reImage ;
}
