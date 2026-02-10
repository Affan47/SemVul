test_empty_SDSs()
{
    int32 sd_id, sds_id, sds_index;
    int32 dimsizes[RANK];
    HDF_CHUNK_DEF c_def;
    int32 flag;
    uintn info_count = 0;
    comp_coder_t comp_type;
    comp_info c_info;
    int ii, jj;
    intn status;
    int num_errs = 0;


    sd_id = SDstart(NODATA_FILE, DFACC_CREATE);
    CHECK(sd_id, FAIL, "test_empty_SDSs: SDstart");


    dimsizes[0] = Y_LENGTH2;
    dimsizes[1] = X_LENGTH2;


    sds_id = SDcreate(sd_id, "Contiguous-No-Data", DFNT_INT16, RANK, dimsizes);
    CHECK(sds_id, FAIL, "test_empty_SDSs: SDcreate 'Contiguous-No-Data'");
    status = SDendaccess(sds_id);
    CHECK(status, FAIL, "test_empty_SDSs: SDendaccess 'Contiguous-No-Data'");


    sds_id = SDcreate(sd_id, "Compressed-No-Data", DFNT_INT16, RANK, dimsizes);
    CHECK(sds_id, FAIL, "test_empty_SDSs: SDcreate 'Compressed-No-Data'");

    HDmemset(&c_info, 0, sizeof(c_info));
    comp_type = COMP_CODE_SKPHUFF;
    c_info.skphuff.skp_size = 4;
    status = SDsetcompress(sds_id, comp_type, &c_info);
    CHECK(status, FAIL, "test_empty_SDSs: SDsetcompress 'Compressed-No-Data'");
    status = SDendaccess(sds_id);
    CHECK(status, FAIL, "test_empty_SDSs: SDendaccess 'Compressed-No-Data'");


    dimsizes[0] = SD_UNLIMITED;
    sds_id = SDcreate(sd_id, "Extend-No-Data", DFNT_INT16, RANK, dimsizes);
    CHECK(sds_id, FAIL, "test_empty_SDSs: SDcreate 'Extend-No-Data'");
    status = SDendaccess(sds_id);
    CHECK(status, FAIL, "test_empty_SDSs: SDendaccess 'Extend-No-Data'");


    for (ii = 0; ii < NUM_SDS; ii++)
    {
  sds_id = SDselect(sd_id, ii);
  CHECK_IND(sds_id, FAIL, "test_empty_SDSs: SDselect", ii);

  info_count = SDgetdatainfo(sds_id, NULL, 0, 0, NULL, NULL);
  CHECK_IND(info_count, FAIL, "test_empty_SDSs: SDgetdatainfo", ii);
  VERIFY(info_count, 0, "test_empty_SDSs: SDgetdatainfo");

  status = SDendaccess(sds_id);
  CHECK_IND(status, FAIL, "test_empty_SDSs: SDendaccess", ii);
    }


    status = SDend(sd_id);
    CHECK(status, FAIL, "test_empty_SDSs: SDend");


    sd_id = SDstart(NODATA_FILE, DFACC_READ);
    CHECK(sd_id, FAIL, "test_empty_SDSs: SDstart");


    for (ii = 0; ii < NUM_SDS; ii++) {
        sds_id = SDselect(sd_id, ii);
        CHECK_IND(sds_id, FAIL, "test_empty_SDSs: SDselect", ii);

        info_count = SDgetdatainfo(sds_id, NULL, 0, 0, NULL, NULL);
        CHECK_IND(info_count, FAIL, "test_empty_SDSs: SDgetdatainfo", ii);
        VERIFY(info_count, 0, "test_empty_SDSs: SDgetdatainfo");

        status = SDendaccess(sds_id);
        CHECK_IND(status, FAIL, "test_empty_SDSs: SDendaccess", ii);
    }

    status = SDend(sd_id);
    CHECK(status, FAIL, "test_empty_SDSs: SDend");


    return num_errs;
}
