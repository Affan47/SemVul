gent_opaque(void)
{
    hid_t file, type, dataset, space;
    char test[100][2];
    int x;
    hsize_t dim = 2;

    for(x = 0; x < 100; x++){
        test[x][0] = x;
        test[x][1] = 99 - x;
    }


    space = H5Screate_simple(1, &dim, NULL);


    file = H5Fcreate(FILE19, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);


    type = H5Tcreate(H5T_OPAQUE, sizeof(char) * 100 * 2);
    H5Tset_tag(type, "test opaque type");


    dataset = H5Dcreate2(file, "opaque test", type, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);


    H5Dwrite(dataset, type, H5S_ALL, H5S_ALL, H5P_DEFAULT, test);

    H5Tclose(type);
    H5Sclose(space);
    H5Dclose(dataset);
    H5Fclose(file);
}
