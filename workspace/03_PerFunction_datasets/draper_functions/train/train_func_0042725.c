count_udtypes(int ncid) {
    int ntypes = 0;
    int numgrps;
    int *ncids;
    int i;
    int format;

    NC_CHECK( nc_inq_format(ncid, &format) );

    if (format == NC_FORMAT_NETCDF4) {

	NC_CHECK( nc_inq_typeids(ncid, &ntypes, NULL) ) ;
	NC_CHECK( nc_inq_grps(ncid, &numgrps, NULL) ) ;
	ncids = (int *) emalloc(sizeof(int) * (numgrps + 1));
	NC_CHECK( nc_inq_grps(ncid, NULL, ncids) ) ;

	for (i=0; i < numgrps; i++) {
	    ntypes += count_udtypes(ncids[i]);
	}
	free(ncids);
    }
    return ntypes;
}
