gent_bitfields(void)
{
    hid_t  file, grp=-1, type=-1, space=-1, dset=-1;
    size_t  i;
    hsize_t  nelmts;
    unsigned char buf[32];

    file = H5Fcreate(FILE20, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    if((grp = H5Gcreate2(file, "typetests", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) goto error;


    nelmts = sizeof(buf);
    if((type = H5Tcopy(H5T_STD_B8LE)) < 0 ||
            (space = H5Screate_simple(1, &nelmts, NULL)) < 0 ||
            (dset = H5Dcreate2(grp, "bitfield_1", type, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0)
        goto error;

    for(i = 0; i < sizeof buf; i++)
        buf[i] = (unsigned char)0xff ^ (unsigned char)i;
    if(H5Dwrite(dset, type, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf) < 0)
        goto error;
    if(H5Sclose(space) < 0) goto error;
    if(H5Tclose(type) < 0) goto error;
    if(H5Dclose(dset) < 0) goto error;


    nelmts = sizeof(buf)/2;
    if((type = H5Tcopy(H5T_STD_B16LE)) < 0 ||
            (space = H5Screate_simple(1, &nelmts, NULL)) < 0 ||
            (dset = H5Dcreate2(grp, "bitfield_2", type, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0)
        goto error;
    for(i = 0; i < sizeof buf; i++)
        buf[i] = (unsigned char)0xff ^ (unsigned char)i;
    if(H5Dwrite(dset, type, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf) < 0)
        goto error;
    if(H5Sclose(space) < 0) goto error;
    if(H5Tclose(type) < 0) goto error;
    if(H5Dclose(dset) < 0) goto error;
    if(H5Gclose(grp) < 0) goto error;
    H5Fclose(file);

    error:
    H5E_BEGIN_TRY {
        H5Gclose(grp);
        H5Tclose(type);
        H5Sclose(space);
        H5Dclose(dset);
    } H5E_END_TRY;
}
