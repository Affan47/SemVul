sinfo_new_plot_gaussian (cpl_image   * image,
                         double     * parlist )
{
    int col, row ;
    cpl_image * retImage ;
    double xdat[2] ;
    int ilx=0;
    int ily=0;
    float* podata=NULL;

    if ( image == NULL )
    {
        sinfo_msg_error("no input image given!") ;
        return NULL ;
    }
    ilx=cpl_image_get_size_x(image);
    ily=cpl_image_get_size_y(image);

    if ( parlist == NULL )
    {
        sinfo_msg_error("no Gaussian parameters given!") ;
        return NULL ;
    }

    retImage = cpl_image_new (ilx, ily, CPL_TYPE_FLOAT) ;
    podata=cpl_image_get_data_float(retImage);
    for ( row = 0 ; row < ily ; row++ )
    {
        for ( col = 0 ; col < ilx ; col++ )
        {
            xdat[0] = (double) col ;
            xdat[1] = (double) row ;
            podata[col+row*ilx] = sinfo_new_gaussian_ellipse( xdat , parlist) ;
        }
    }

    return retImage ;
}
