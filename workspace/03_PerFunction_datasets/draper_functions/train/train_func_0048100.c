test_1f(hid_t file)
{
    hid_t	dcpl=-1;
    hid_t	space=-1;
    hid_t	dset=-1;
    hsize_t	cur_size[1];
    hsize_t	max_size[1];

    TESTING("multiple external files");

    if((dcpl = H5Pcreate(H5P_DATASET_CREATE)) < 0) goto error;
    cur_size[0] = max_size[0] = 100;
    if(H5Pset_external(dcpl, "ext1.data", (off_t)0,
	(hsize_t)(max_size[0]*sizeof(int)/4)) < 0) goto error;
    if(H5Pset_external(dcpl, "ext2.data", (off_t)0,
	(hsize_t)(max_size[0]*sizeof(int)/4)) < 0) goto error;
    if(H5Pset_external(dcpl, "ext3.data", (off_t)0,
	(hsize_t)(max_size[0]*sizeof(int)/4)) < 0) goto error;
    if(H5Pset_external(dcpl, "ext4.data", (off_t)0,
	(hsize_t)(max_size[0]*sizeof(int)/4)) < 0) goto error;
    if((space = H5Screate_simple(1, cur_size, max_size)) < 0) goto error;
    if((dset = H5Dcreate2(file, "dset6", H5T_NATIVE_INT, space, H5P_DEFAULT, dcpl, H5P_DEFAULT)) < 0)
	goto error;
    if(H5Dclose(dset) < 0) goto error;
    if(H5Sclose(space) < 0) goto error;
    if(H5Pclose(dcpl) < 0) goto error;

    PASSED();
    return 0;

error:
    H5E_BEGIN_TRY {
	H5Dclose(dset);
	H5Pclose(dcpl);
	H5Sclose(space);
    } H5E_END_TRY;
    return 1;
}
