sinfo_new_mult_row_to_image( cpl_image *im, Vector *row )
{
    cpl_image *image=NULL;
    int         i=0;
    int         j=0;
    int ilx=0;
    int ily=0;
    float* pidata=NULL;
    float* podata=NULL;


    if ( im == NULL || row == NULL )
    {
        sinfo_msg_error ("null image or null row") ;
        return NULL ;
    }
    ilx=cpl_image_get_size_x(im);
    ily=cpl_image_get_size_y(im);
    pidata=cpl_image_get_data_float(im);

    if ( ilx != row -> n_elements )
    {
        sinfo_msg_error("image and row size not compatible") ;
        return NULL ;
    }

    if ( NULL == (image = cpl_image_duplicate (im)) )
    {
        sinfo_msg_error ("cannot copy image") ;
        return NULL ;
    }
    podata=cpl_image_get_data_float(image);

    for (i = 0 ; i < ilx ; i++ )
    {
        for (j = 0 ; j < ily ; j++)
        {
            if ( !isnan(pidata[i + j*(ilx)]) )
            {
                podata[i + j*(ilx)] = pidata[i + j*(ilx)] * row -> data[i] ;
            }
        }
    }
    return image ;
}
