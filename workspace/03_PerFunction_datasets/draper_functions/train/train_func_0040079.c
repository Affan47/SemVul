create_hdf_file(const char *name)
{
    hid_t fid;
    hid_t gid,gid2;
    hid_t tid;
    hid_t dcpl;
    hsize_t chunk_dims[MISC13_RANK];
    herr_t ret;


    fid=H5Fcreate(name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    CHECK(fid, FAIL, "H5Fcreate");


    dcpl = H5Pcreate(H5P_DATASET_CREATE);
    CHECK(dcpl, FAIL, "H5Pcreate");


    ret = H5Pset_layout(dcpl, H5D_CHUNKED);
    CHECK(ret, FAIL, "H5Pset_layout");


    chunk_dims[0] = MISC13_CHUNK_DIM1;
    chunk_dims[1] = MISC13_CHUNK_DIM2;
    ret = H5Pset_chunk(dcpl, MISC13_RANK, chunk_dims);
    CHECK(ret, FAIL, "H5Pset_chunk");


    create_dataset(fid, MISC13_DSET1_NAME, H5P_DEFAULT);


    create_dataset(fid, MISC13_DSET2_NAME, dcpl);


    tid = H5Tcopy(H5T_NATIVE_INT);
    CHECK(tid, FAIL, "H5Tcopy");


    ret = H5Tcommit2(fid, MISC13_DTYPE_NAME, tid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    CHECK(ret, FAIL, "H5Tcommit2");


    ret = H5Tclose(tid);
    CHECK(ret, FAIL, "H5Tclose");


    gid = H5Gcreate2(fid, MISC13_GROUP1_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    CHECK(gid, FAIL, "H5Gcreate2");


    gid2 = H5Gcreate2(gid, MISC13_GROUP2_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    CHECK(gid2, FAIL, "H5Gcreate2");


    ret = H5Gclose(gid2);
    CHECK(ret, FAIL, "H5Gclose");


    create_dataset(gid, MISC13_DSET1_NAME, H5P_DEFAULT);


    create_dataset(gid, MISC13_DSET2_NAME, dcpl);


    tid = H5Tcopy(H5T_NATIVE_INT);
    CHECK(tid, FAIL, "H5Tcopy");


    ret = H5Tcommit2(gid, MISC13_DTYPE_NAME, tid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    CHECK(ret, FAIL, "H5Tcommit2");


    ret = H5Tclose(tid);
    CHECK(ret, FAIL, "H5Tclose");


    ret = H5Gclose(gid);
    CHECK(ret, FAIL, "H5Gclose");


    ret = H5Pclose(dcpl);
    CHECK(ret, FAIL, "H5Pclose");


    ret = H5Fclose(fid);
    HDassert(ret >= 0);
    CHECK(ret, FAIL, "H5Fclose");
}
