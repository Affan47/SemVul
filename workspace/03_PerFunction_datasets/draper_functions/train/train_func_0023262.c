test_2 (hid_t fapl)
{
    hid_t	file = -1;
    H5F_t 	*f = NULL;
    H5HG_t	obj[1024];
    uint8_t	out[1024];
    uint8_t	in[1024];
    int		i;
    size_t	size;
    int		nerrors = 0;
    char	filename[1024];

    TESTING("monotonically decreasing lengths");


    h5_fixname(FILENAME[1], fapl, filename, sizeof filename);
    if((file = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0)
	goto error;
    if(NULL == (f = (H5F_t *)H5I_object(file))) {
	H5_FAILED();
	puts("    Unable to create file");
	goto error;
    }


    for (i=0; i<1024; i++) {
	size = 1024-i;
	memset (out, 'A'+i%26, size);
	H5Eclear2(H5E_DEFAULT);
	if (H5HG_insert (f, H5P_DATASET_XFER_DEFAULT, size, out, obj+i)<0) {
	    H5_FAILED();
	    puts("    Unable to insert object into global heap");
	    nerrors++;
	}
    }


    for (i=0; i<1024; i++) {
	size = 1024-i;
	memset (out, 'A'+i%26, size);
	H5Eclear2(H5E_DEFAULT);
	if (NULL==H5HG_read (f, H5P_DATASET_XFER_DEFAULT, obj+i, in, NULL)) {
	    H5_FAILED();
	    puts("    Unable to read object");
	    nerrors++;
	} else if (memcmp (in, out, size)) {
	    H5_FAILED();
	    puts("    Value read doesn't match value written");
	    nerrors++;
	}
    }

    if (H5Fclose(file)<0) goto error;
    if (nerrors) goto error;
    PASSED();
    return 0;

 error:
    H5E_BEGIN_TRY {
	H5Fclose(file);
    } H5E_END_TRY;
    return MAX(1, nerrors);
}
