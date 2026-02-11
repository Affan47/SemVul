numrecvars(ncid, recvarids)
     int ncid;
     int *recvarids;
{
    int ndims, iv, nvars;
    int nrecvars;
    int recdimid;
    int dimids[H4_MAX_VAR_DIMS];

    if (ncinquire(ncid, NULL, &nvars, NULL, &recdimid) == -1)
      return -1;
    if (recdimid == -1)
      return 0;
    nrecvars = 0;
    for (iv = 0; iv < nvars; iv++) {
	if (ncvarinq(ncid, iv, NULL, NULL, &ndims, dimids, NULL) == -1)
	  return -1;
	if (ndims > 0 && dimids[0] == recdimid) {
	    if (recvarids)
	      recvarids[nrecvars] = iv;
	    nrecvars++;
	}
    }
    return nrecvars;
}
