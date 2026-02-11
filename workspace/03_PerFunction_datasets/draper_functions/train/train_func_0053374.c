copy_types(int igrp, int ogrp)
{
    int stat = NC_NOERR;
    int ntypes;
    nc_type *types = NULL;
    int numgrps;
    int *grpids = NULL;
    int i;

    NC_CHECK(nc_inq_typeids(igrp, &ntypes, NULL));

    if(ntypes > 0) {
	types = (nc_type *) emalloc(ntypes * sizeof(nc_type));
	NC_CHECK(nc_inq_typeids(igrp, &ntypes, types));
	for (i = 0; i < ntypes; i++) {
	    NC_CHECK(copy_type(igrp, types[i], ogrp));
	}
	free(types);
    }


    NC_CHECK(nc_inq_grps(igrp, &numgrps, NULL));
    if(numgrps > 0) {
	grpids = (int *)emalloc(sizeof(int) * numgrps);
	NC_CHECK(nc_inq_grps(igrp, &numgrps, grpids));
	for(i = 0; i < numgrps; i++) {
	    int ogid;


	    NC_CHECK(get_grpid(grpids[i], ogrp, &ogid));
	    NC_CHECK(copy_types(grpids[i], ogid));
	}
	free(grpids);
    }
    return stat;
}
