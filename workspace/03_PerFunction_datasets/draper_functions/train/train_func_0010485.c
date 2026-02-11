test_compressed_SDSs(int32 fid)
{
    int32     sds_id, esds_id, usds_id;
    int32     start[2], edges[2], dim_sizes[2];
    comp_coder_t comp_type;
    comp_info c_info;
    int32     data[Y_LENGTH][X_LENGTH];
    intn      status;
    int       i, j;
    int   num_errs = 0;


    for (j = 0; j < Y_LENGTH; j++)
    {
        for (i = 0; i < X_LENGTH; i++)
                data[j][i] = (i + j) + 1;
    }
    dim_sizes[0] = Y_LENGTH;
    dim_sizes[1] = X_LENGTH;


    sds_id = SDcreate(fid, "CompressedData", DFNT_INT32, RANK, dim_sizes);
    CHECK(sds_id, FAIL, "test_compressed_SDSs: SDcreate 'CompressedData'");

    esds_id = SDcreate(fid, "Compressed-No-Data", DFNT_INT32, RANK, dim_sizes);
    CHECK(esds_id, FAIL, "test_compressed_SDSs: SDcreate 'Compressed-No-Data'");

    usds_id = SDcreate(fid, "Non-CompressedData", DFNT_INT32, RANK, dim_sizes);
    CHECK(usds_id, FAIL, "test_compressed_SDSs: SDcreate 'Non-CompressedData'");

    comp_type = COMP_CODE_DEFLATE;
    c_info.deflate.level = 6;
    status = SDsetcompress(sds_id, comp_type, &c_info);
    CHECK(status, FAIL, "test_compressed_SDSs: SDsetcompress 'CompressedData'");

    status = SDsetcompress(esds_id, comp_type, &c_info);
    CHECK(status, FAIL, "test_compressed_SDSs: SDsetcompress 'Compressed-No-Data'");


    start[0] = 0;
    start[1] = 0;
    edges[0] = Y_LENGTH;
    edges[1] = X_LENGTH;


    status = SDwritedata(sds_id, start, NULL, edges, (VOIDP)data);
    CHECK(status, FAIL, "test_compressed_SDSs: SDwritedata");


    status = SDwritedata(usds_id, start, NULL, edges, (VOIDP)data);
    CHECK(status, FAIL, "test_compressed_SDSs: SDwritedata");


    status = SDendaccess(sds_id);
    CHECK(status, FAIL, "test_compressed_SDSs: SDendaccess 'CompressedData'");

    status = SDendaccess(esds_id);
    CHECK(status, FAIL, "test_compressed_SDSs: SDendaccess 'Compressed-No-Data'");

    status = SDendaccess(usds_id);
    CHECK(status, FAIL, "test_compressed_SDSs: SDendaccess 'Non-CompressedData'");


    check_datasizes(fid, "CompressedData", 59, Y_LENGTH*X_LENGTH*SIZE_INT32, &num_errs);


    check_datasizes(fid, "Compressed-No-Data", 0, 0, &num_errs);


    check_datasizes(fid, "Non-CompressedData", Y_LENGTH*X_LENGTH*SIZE_INT32, Y_LENGTH*X_LENGTH*SIZE_INT32, &num_errs);


    return num_errs;
}
