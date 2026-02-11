test_userblock_alignment_helper1(hid_t fcpl, hid_t fapl)
{
    hid_t fid;
    int curr_num_errs = GetTestNumErrs();
    herr_t ret;


    fid = H5Fcreate(FILE1, H5F_ACC_TRUNC, fcpl, fapl);
    CHECK(fid, FAIL, "H5Fcreate");


    if(fid > 0) {
        hid_t gid;
        hid_t sid;
        hid_t did;
        int val = 2;


        gid = H5Gcreate2(fid, "group1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        CHECK(gid, FAIL, "H5Gcreate2");


        sid = H5Screate(H5S_SCALAR);
        CHECK(sid, FAIL, "H5Screate");
        did = H5Dcreate2(gid, "dataset", H5T_NATIVE_INT, sid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        CHECK(did, FAIL, "H5Dcreate2");


        ret = H5Sclose(sid);
        CHECK(ret, FAIL, "H5Sclose");


        ret = H5Dwrite(did, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, &val);
        CHECK(ret, FAIL, "H5Dwrite");


        ret = H5Dclose(did);
        CHECK(ret, FAIL, "H5Dclose");


        ret = H5Gclose(gid);
        CHECK(ret, FAIL, "H5Gclose");


        ret = H5Fclose(fid);
        CHECK(ret, FAIL, "H5Fclose");
    }

    return((GetTestNumErrs() == curr_num_errs) ? 0 : -1);
}
