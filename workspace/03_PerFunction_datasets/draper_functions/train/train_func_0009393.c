sinfo_new_slice_cube (cpl_imagelist * cube, int x, int y )
{
    cpl_image * retImage=NULL ;
    int col=0, row=0, z=0 ;
    int inp=0;
    int ilx=0;
    int ily=0;
    cpl_image* img=NULL;
    float* podata=NULL;
    float* pidata=NULL;

    if ( cube == NULL )
    {
        sinfo_msg_error("no cube given!") ;
        return NULL ;
    }
    if ( x > 31 || y > 31 )
    {
        sinfo_msg_warning("wrong x or y values!") ;
    }

    img=cpl_imagelist_get(cube,0);
    ilx=cpl_image_get_size_x(img);
    ily=cpl_image_get_size_y(img);
    inp=cpl_imagelist_get_size(cube);
    if ( x < 0 )
    {

        if ( NULL == (retImage = cpl_image_new(ilx, inp, CPL_TYPE_FLOAT)) )
        {
            sinfo_msg_error("could not allocate memory!") ;
            return NULL ;
        }
        podata=cpl_image_get_data_float(retImage);
        for ( z = 0 ; z < inp ; z++ )
        {

            pidata=cpl_image_get_data_float(cpl_imagelist_get(cube,z));
            for ( col = 0 ; col < ilx ; col++ )
            {
                podata[col+z*ilx] = pidata[col+y*ilx] ;
            }
        }
    }
    else if ( y < 0 )
    {

        if ( NULL == (retImage = cpl_image_new(ily, inp,CPL_TYPE_FLOAT)) )
        {
            sinfo_msg_error("could not allocate memory!") ;
            return NULL ;
        }
        podata=cpl_image_get_data_float(retImage);

        for ( z = 0 ; z < inp ; z++ )
        {
            pidata=cpl_image_get_data_float(cpl_imagelist_get(cube,z));
            for ( row = 0 ; row < ily ; row++ )
            {
                podata[row+z*ily] = pidata[x+row*ily] ;
            }
        }
    }
    else
    {
        sinfo_msg_error("wrong input!") ;
        return NULL ;
    }
    return retImage ;
}
