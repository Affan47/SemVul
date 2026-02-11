do_fopen(parameters *param, char *fname, file_descr *fd , int flags)
{
    int ret_code = SUCCESS;

    switch (param->io_type) {
    case POSIXIO:
        if (flags & (SIO_CREATE | SIO_WRITE))
            fd->posixfd = POSIXCREATE(fname);
        else
            fd->posixfd = POSIXOPEN(fname, O_RDONLY);

        if (fd->posixfd < 0 ) {
            HDfprintf(stderr, "POSIX File Open failed(%s)\n", fname);
            GOTOERROR(FAIL);
        }

        break;

    case HDF5:

        fapl = set_vfd(param);

        if (fapl < 0) {
            fprintf(stderr, "HDF5 Property List Create failed\n");
            GOTOERROR(FAIL);
        }


        if (flags & (SIO_CREATE | SIO_WRITE)) {
            fd->h5fd = H5Fcreate(fname, H5F_ACC_TRUNC, H5P_DEFAULT, fapl);
        } else {
            fd->h5fd = H5Fopen(fname, H5F_ACC_RDONLY, fapl);
        }


        if (fd->h5fd < 0) {
            fprintf(stderr, "HDF5 File Create failed(%s)\n", fname);
            GOTOERROR(FAIL);
        }
        break;
    }

done:
    return ret_code;
}
