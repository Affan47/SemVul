test_dangle_datatype2(H5F_close_degree_t degree)
{
    char	filename[1024];
    hid_t       fid;
    hid_t       fapl;
    hid_t       did;
    hid_t       sid;
    hid_t       tid;

    TESTING("    dangling named datatype ID used by dataset");

    if(H5open() < 0)
        TEST_ERROR;


    if((fapl = H5Pcreate(H5P_FILE_ACCESS)) < 0)
        TEST_ERROR;


    if(H5Pset_fclose_degree(fapl, degree) < 0)
        TEST_ERROR;

    h5_fixname(FILENAME[0], H5P_DEFAULT, filename, sizeof filename);
    if((fid = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0)
        TEST_ERROR;

    if((tid = H5Tcopy(H5T_NATIVE_INT)) < 0)
        TEST_ERROR;

    if(H5Tcommit2(fid, TYPENAME, tid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT) < 0)
        TEST_ERROR;


    if((sid = H5Screate(H5S_SCALAR)) < 0)
        TEST_ERROR;
    if((did = H5Dcreate2(fid, DSETNAME, tid, sid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0)
        TEST_ERROR;
    if(H5Sclose(sid) < 0)
        TEST_ERROR;

    if(degree == H5F_CLOSE_SEMI) {
        H5E_BEGIN_TRY {
            if(H5Fclose(fid) >= 0)
                TEST_ERROR;
        } H5E_END_TRY;
    }
    else
        if(H5Fclose(fid) < 0)
            TEST_ERROR;

    if(h5_get_file_size(filename, fapl) < 0)
        TEST_ERROR;

    if(H5Pclose(fapl) < 0)
        TEST_ERROR;

    if(H5close() < 0)
        TEST_ERROR;


    HDremove(filename);

    PASSED();
    return 0;

error:
    return 1;
}
