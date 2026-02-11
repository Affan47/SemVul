test_checkempty()
{
    int32 fid;
    intn status;
    int num_errs = 0;


    TESTING("functions involving empty data sets (temptySDSs.c)");


    fid = SDstart(FILE_NAME, DFACC_CREATE);
    CHECK(fid, FAIL, "In test_checkempty: SDstart");

    num_errs = num_errs + test_nonspecial_SDSs(fid);
    num_errs = num_errs + test_compressed_SDSs(fid);
    num_errs = num_errs + test_chunked_SDSs(fid);
    num_errs = num_errs + test_unlimited_SDSs(fid);


    status = SDend(fid);
    CHECK(status, FAIL, "In test_checkempty: SDend");


    num_errs = num_errs + test_with_existing_file();


    num_errs = num_errs + test_getchunkinfo();

    if (num_errs == 0) PASSED();
    return num_errs;
}
