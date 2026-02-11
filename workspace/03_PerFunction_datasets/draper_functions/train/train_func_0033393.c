H5FD_family_query(const H5FD_t * _file, unsigned long *flags )
{
    const H5FD_family_t	*file = (const H5FD_family_t*)_file;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    if(flags) {
        *flags = 0;
        *flags |= H5FD_FEAT_AGGREGATE_METADATA;
        *flags |= H5FD_FEAT_ACCUMULATE_METADATA;
        *flags |= H5FD_FEAT_DATA_SIEVE;
        *flags |= H5FD_FEAT_AGGREGATE_SMALLDATA;


        if(file && file->repart_members)
            *flags |= H5FD_FEAT_DIRTY_SBLK_LOAD;
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
