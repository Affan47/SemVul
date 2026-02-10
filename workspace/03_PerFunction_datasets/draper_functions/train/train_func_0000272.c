sinfo_new_fit_params( int n_params )
{
    FitParams ** new_params =NULL;
    FitParams  * temp_params =NULL;
    float * temp_fit_mem =NULL;
    float * temp_derv_mem=NULL;
    int i ;


    if ( n_params <= 0 )
    {
        sinfo_msg_error (" wrong number of lines to fit\n") ;
        return NULL ;
    }

    if (NULL==(new_params=(FitParams **) cpl_calloc ( n_params ,
                                         sizeof (FitParams*) ) ) )
    {
        sinfo_msg_error (" could not allocate memory\n") ;
        return NULL ;
    }
    if ( NULL == (temp_params = cpl_calloc ( n_params , sizeof (FitParams) ) ) )
    {
        sinfo_msg_error (" could not allocate memory\n") ;
        return NULL ;
    }
    if ( NULL == (temp_fit_mem = (float *) cpl_calloc( n_params*MAXPAR,
                                     sizeof (float) ) ) )
    {
        sinfo_msg_error (" could not allocate memory\n") ;
        return NULL ;
    }


    if ( NULL == (temp_derv_mem   =
             (float *) cpl_calloc( n_params*MAXPAR, sizeof (float) ) ) )
    {
        sinfo_msg_error (" could not allocate memory\n") ;
        return NULL ;
    }

    for ( i = 0 ; i < n_params ; i ++ )
    {
        new_params[i] = temp_params+i;
        new_params[i] -> fit_par    = temp_fit_mem+i*MAXPAR;
        new_params[i] -> derv_par   = temp_derv_mem+i*MAXPAR;
        new_params[i] -> column     = 0 ;
        new_params[i] -> line       = 0 ;
        new_params[i] -> wavelength = 0. ;
        new_params[i] -> n_params   = n_params ;
    }

    return new_params ;
}
