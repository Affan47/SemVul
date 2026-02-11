check_datasizes(
		int32 fid,
		char* sds_name,
		int32 comp_size_check,
		int32 uncomp_size_check,
		int* ret_num_errs	 )
{
    int32 sds_id, sds_index;
    intn status;
    int num_errs = 0;
    char mesg[80];
    int32 uncomp_size=0, comp_size=0;


    sds_index = SDnametoindex(fid, sds_name);
    sprintf(mesg, "check_datasizes: SDnametoindex (%s)", sds_name);
    CHECK(sds_index, FAIL, mesg);


    sds_id = SDselect(fid, sds_index);
    CHECK(sds_id, FAIL, "check_datasizes: SDselect");


    status = SDgetdatasize(sds_id, &comp_size, &uncomp_size);
    sprintf(mesg, "SDgetdatasize: SDS named (%s)", sds_name);
    CHECK(status, FAIL, mesg);
    VERIFY(comp_size, comp_size_check, mesg);
    VERIFY(uncomp_size, uncomp_size_check, mesg);


    status = SDendaccess(sds_id);
    CHECK(status, FAIL, "check_datasizes: SDendaccess");

    *ret_num_errs = num_errs;
}
