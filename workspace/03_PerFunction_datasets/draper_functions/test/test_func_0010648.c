sinfo_new_wave_map_slit ( float ** acoefs,
                         int      n_acoefs,
                         int      n_rows,
                         int      n_columns )
{
    cpl_image * newIm=NULL ;
    float lambda=0 ;
    float offset=0 ;
    int col=0;
    int row=0 ;
    int i=0 ;
    float row_index=0 ;
    float* podata=NULL;
    if ( NULL == acoefs )
    {
        sinfo_msg_error (" no coefficient sinfo_matrix given!") ;
        return NULL ;
    }


    if ( NULL == (newIm = cpl_image_new(n_columns , n_rows,CPL_TYPE_FLOAT)) )
    {
        sinfo_msg_error ("could not allocate new image!") ;
        return NULL ;
    }
    podata=cpl_image_get_data_float(newIm);


    offset = (float)(n_rows - 1) / 2. ;


    for ( col = 0 ; col < n_columns ; col++ )
    {

        for ( row = 0 ; row < n_rows ; row++ )
        {
            lambda = 0. ;
            row_index = (float)row - offset ;
            for ( i = 0 ; i < n_acoefs ; i++ )
            {
                lambda += acoefs[i][col] * pow(row_index, i) ;
            }
            podata[col+row*n_columns] = lambda ;
        }
    }
    return newIm ;
}
