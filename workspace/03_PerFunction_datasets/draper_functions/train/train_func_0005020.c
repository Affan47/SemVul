test_complicated_compound(void)
{
    hid_t   dtype;
    int     nmembs;
    H5T_class_t type_class;
    char   *line = NULL;
    FILE   *fp = NULL;
    size_t  size = 1024;
    char   *srcdir = getenv("srcdir");
    char    filename[1024]="";

    TESTING3("        text for complicated compound types");


    if(srcdir) {
        HDstrcpy(filename, srcdir);
        HDstrcat(filename, "/");
    }
    HDstrcat(filename, INPUT_FILE);


    fp = HDfopen(filename, "r");
    if(fp == NULL) {
        printf( "Could not find file %s. Try set $srcdir \n", filename);
        goto out;
    }


    if((line = (char*)HDcalloc(size, sizeof(char)))==NULL)
        goto out;
    if(HDfgets(line, (int)size, fp)==NULL)
        goto out;
    while(HDstrlen(line)==size-1) {
        size *= 2;
        if(line)
            HDfree(line);
        if((line = (char*)HDcalloc(size, sizeof(char)))==NULL)
            goto out;
        if(HDfseek(fp, 0L, SEEK_SET)!=0)
            goto out;
        if(HDfgets(line, (int)size, fp)==NULL)
            goto out;
    }

    HDfclose(fp);
    fp = NULL;

    if((dtype = H5LTtext_to_dtype(line, H5LT_DDL))<0)
        goto out;

    if((type_class = H5Tget_class(dtype))<0)
        goto out;
    if(type_class != H5T_COMPOUND)
        goto out;


    if((nmembs = H5Tget_nmembers(dtype))<0)
        goto out;
    if(nmembs != 101)
        goto out;

    if(line)
        HDfree(line);

    PASSED();
    return 0;

out:

    if(line)
        HDfree(line);
    if(fp)
        HDfclose(fp);

    H5_FAILED();
    return -1;
}
