gifti_darray_nvals(const giiDataArray * da)
{
    long long ndim = 1;
    int       c;

    if(!da){ fprintf(stderr,"** GDND, no ptr\n"); return 0; }

    if( ! gifti_valid_num_dim(da->num_dim, 0) ) {
        fprintf(stderr,"** giiDataArray has illegal num_dim = %d\n",
                da->num_dim);
        return 0;
    }

    for( c = 0; c < da->num_dim; c++ ) ndim *= da->dims[c];

    if( ndim <= 0 ) {
        gifti_disp_DataArray("** bad Dim list in ", da, 0);
        return 0;
    }

    return ndim;
}
