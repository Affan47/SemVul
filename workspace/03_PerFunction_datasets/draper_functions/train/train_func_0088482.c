get_grpid(int igrp, int parid, int *ogrpp) {
    int stat = NC_NOERR;
    int ogid;
#ifdef USE_NETCDF4
    int inparid;


    stat = nc_inq_grp_parent(igrp, &inparid);
    if(stat == NC_NOERR) {
	char grpname[NC_MAX_NAME + 1];
	NC_CHECK(nc_inq_grpname(igrp, grpname));
	NC_CHECK(nc_inq_grp_ncid(parid, grpname, &ogid));
    } else if(stat == NC_ENOGRP) {
	ogid = parid;
	stat = NC_NOERR;
    } else {
	NC_CHECK(stat);
    }
#else
    ogid = parid;
#endif
    *ogrpp = ogid;
    return stat;
}
