sinfo_new_average_cube_to_image(cpl_imagelist * cube)
{
    cpl_image  *      im ;
    int        i, j, nz ;
    int ilx=0;
    int ily=0;
    int inp=0;
    float* pidata=NULL;
    float* podata=NULL;
    cpl_image* i_img=NULL;

    if ( cube == NULL )
    {
        sinfo_msg_error ("null cube") ;
        return NULL ;
    }
    inp=cpl_imagelist_get_size(cube);
    i_img=cpl_imagelist_get(cube,0);
    ilx=cpl_image_get_size_x(i_img);
    ily=cpl_image_get_size_y(i_img);


    if (NULL == (im = cpl_image_new (ilx, ily,CPL_TYPE_FLOAT )) )
    {
        sinfo_msg_error ("cannot allocate new image") ;
        return NULL ;
    }


    podata=cpl_image_get_data_float(im);
    for ( i = 0 ; i < (int) ilx*ily ; i++ )
    {
        nz = 0 ;
        for ( j = 0 ; j < inp ; j ++ )
        {
          i_img=cpl_imagelist_get(cube,j);
      pidata=cpl_image_get_data_float(i_img);
            if ( !isnan(pidata[i]) )
            {
                nz ++ ;
                podata[i] += pidata[i] ;
            }
        }


        if ( nz >= 1 )
        {
            podata[i] /= nz ;
        }
        else if (nz == 0)
        {
            podata[i] = ZERO ;
        }
    }

    return im ;
}
