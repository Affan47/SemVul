H5FD_multi_query(const H5FD_t *_f, unsigned long *flags )
{

    _f=_f;


    if(flags) {
        *flags = 0;
        *flags |= H5FD_FEAT_DATA_SIEVE;
        *flags |= H5FD_FEAT_AGGREGATE_SMALLDATA;
    }

    return(0);
}
