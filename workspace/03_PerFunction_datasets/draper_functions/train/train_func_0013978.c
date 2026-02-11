gent_hyperslab(void)
{
    hid_t    fid;
    hsize_t  dims[2]  = {32,4097};
    double   *buf;
    int      i, ret;

    buf = (double*) HDmalloc(32 * 4097 * sizeof(double) );
    for(i = 0; i < 32 * 4097; i++)
        buf[i] = 1;


    fid  = H5Fcreate(FILE57, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    HDassert(fid>=0);

    write_dset(fid,2,dims,"stripmine",H5T_NATIVE_DOUBLE,buf);

    ret = H5Fclose(fid);
    HDassert(ret >= 0);

    HDfree(buf);
}
