sinfo_new_multiply_image_with_spectrum( cpl_image * image,
                                        cpl_image * spectrum )
{
    int col, row ;
    cpl_image * retImage ;


    int ilx=0;
    int ily=0;
    int slx=0;
    int sly=0;

    float* pidata=NULL;
    float* psdata=NULL;
    float* podata=NULL;


    if ( image == NULL )
    {
        sinfo_msg_error(" no image given!") ;
        return NULL ;
    }
    ilx=cpl_image_get_size_x(image);
    ily=cpl_image_get_size_y(image);

    if ( spectrum == NULL )
    {
        sinfo_msg_error(" no spectrum image given!") ;
        return NULL ;
    }
    slx=cpl_image_get_size_x(spectrum);
    sly=cpl_image_get_size_y(spectrum);

    if ( sly != ily )
    {
        sinfo_msg_error(" images are not compatible in pixel length!") ;
        return NULL ;
    }

    if ( NULL == (retImage = cpl_image_duplicate(image)) )
    {
        sinfo_msg_error(" could not copy original image!\n") ;
        return NULL ;
    }

    pidata=cpl_image_get_data_float(image);
    psdata=cpl_image_get_data_float(spectrum);
    podata=cpl_image_get_data_float(retImage);

    for ( col = 0 ; col < ilx ; col++ )
    {
        for ( row = 0 ; row < ily ; row++ )
        {
            if ( !isnan(pidata[col+row*ilx]) &&
                 !isnan(psdata[col+row*ilx]))
            {
                podata[col+row*ilx] = pidata[col+row*ilx] * psdata[row] ;

            }
        }
    }
    return retImage ;
}
