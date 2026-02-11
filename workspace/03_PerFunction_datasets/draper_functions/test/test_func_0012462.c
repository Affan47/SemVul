test_nonSDAPI_ids ()
{
    int32     fid, gr_id, vdata_id, ri_id;
    int32     vdata_ref;
    intn      status;
    int32     dims[2]={4,5};
    hdf_idtype_t id_type;
    intn      num_errs = 0;


    fid = Hopen(IDTYPE_FILE, DFACC_RDWR, 0);
    CHECK(fid, FAIL, "Hopen: tidtype.hdf");


    status = Vstart(fid);
    CHECK(status, FAIL, "Vstart");


    vdata_id = VSattach(fid, -1, "w");
    CHECK(vdata_id, FAIL, "VSattach");
    status = VSsetname(vdata_id, "Vdata_1");
    CHECK(status, FAIL, "VSsetname");


    status = VSdetach(vdata_id);
    CHECK(status, FAIL, "VSdetach");


    status = Vend(fid);
    CHECK(status, FAIL, "Vend");
    status = Hclose(fid);
    CHECK(status, FAIL, "Hclose");


    fid = Hopen(IDTYPE_FILE, DFACC_RDWR, 0);
    CHECK(fid, FAIL, "Hopen: tidtype.hdf");


    status = Vstart(fid);
    CHECK(status, FAIL, "Vstart");


    vdata_ref = VSfind(fid, "Vdata_1");
    CHECK(vdata_ref, FAIL, "VSfind");
    vdata_id = VSattach(fid, vdata_ref, "w");
    CHECK(vdata_id, FAIL, "VSattach");


    id_type = SDidtype(vdata_id);
    VERIFY(id_type, NOT_SDAPI_ID, "SDidtype: id_type");


    status = VSdetach(vdata_id);
    CHECK(status, FAIL, "VSdetach");


    status = Vend(fid);
    CHECK(status, FAIL, "Vend");
    status = Hclose(fid);
    CHECK(status, FAIL, "Hclose");


    fid = Hopen(IDTYPE_FILE, DFACC_RDWR, 0);
    CHECK(fid, FAIL, "Hopen: tidtype.hdf");
    gr_id = GRstart(fid);
    CHECK(gr_id, FAIL, "GRstart");


    ri_id = GRcreate(gr_id, "Empty Image", 3, DFNT_FLOAT32,
		MFGR_INTERLACE_PIXEL, dims);
    CHECK(ri_id, FAIL, "GRcreate");


    id_type = SDidtype(ri_id);
    VERIFY(id_type, NOT_SDAPI_ID, "SDidtype: id_type");


    status = GRendaccess(ri_id);
    CHECK(status, FAIL, "GRendaccess");


    status = GRend(gr_id);
    CHECK(status, FAIL, "GRend");
    status = Hclose(fid);
    CHECK(status, FAIL, "Hclose");


    return num_errs;
}
