fits_set_tile_dim(fitsfile *fptr,
           int ndim,
           long *dims,

           int *status)
{


    int ii;

    if (ndim < 0 || ndim > MAX_COMPRESS_DIM)
    {
        *status = BAD_DIMEN;
        return(*status);
    }

    for (ii = 0; ii < ndim; ii++)
    {
        (fptr->Fptr)->request_tilesize[ii] = dims[ii];
    }

    return(*status);
}
