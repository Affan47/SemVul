test_ncrecinq(path)
     char *path;
{
    int nerrs = 0;
    static char pname[] = "test_ncrecinq";
    int ncid;
    int nrvars;
    int rvarids[VARS];
    long rvarsizes[VARS];
    int tnrvars;
    int trvarids[VARS];
    long trvarsizes[VARS];
    int iv;

    (void) fprintf(stderr, "*** Testing %s ...\t", &pname[5]);

    if ((ncid = ncopen(path, NC_WRITE)) == -1) {
	error("%s: ncopen failed", pname);
	return;
    }


    if (recinq(ncid, &tnrvars, trvarids, trvarsizes) == -1) {
	error("%s: recinq failed", pname);
	ncclose(ncid);
	return;
    }


    if (ncrecinq(ncid, &nrvars, rvarids, rvarsizes) == -1) {
	error("%s: ncrecinq failed", pname);
	ncclose(ncid);
	return;
    }

    if (nrvars != tnrvars) {
	error("ncrecinq returned wrong number of rec vars, %d != %d",
	      nrvars, tnrvars);
	nerrs++;
    }

    for (iv = 0; iv < nrvars; iv++) {
	if (rvarids[iv] != trvarids[iv]) {
	    error("ncrecinq returned wrong record id for var %d",
		  trvarids[iv]);
	    nerrs++;
	}
	if (rvarsizes[iv] != trvarsizes[iv]) {
	    error("ncrecinq returned wrong record size for var %d",
		  trvarids[iv]);
	    nerrs++;
	}
    }

    if (ncredef(ncid) == -1) {
	error("%s: ncredef failed", pname);
	ncclose(ncid);
	return;
    }

    if (ncrecinq(ncid, &nrvars, rvarids, rvarsizes) == -1) {
	error("%s: ncrecinq failed in define mode", pname);
	ncclose(ncid);
	return;
    }
    if (nrvars != tnrvars) {
	error("define mode, ncrecinq returned wrong num of rec vars, %d != %d",
	      nrvars, tnrvars);
	nerrs++;
    }
    for (iv = 0; iv < nrvars; iv++) {
	if (rvarids[iv] != trvarids[iv]) {
	    error("define mode, ncrecinq returned wrong record id for var %d",
		  trvarids[iv]);
	    nerrs++;
	}
	if (rvarsizes[iv] != trvarsizes[iv]) {
	    error("define mode, ncrecinq returned wrong rec size for var %d",
		  trvarids[iv]);
	    nerrs++;
	}
    }

    if (ncclose (ncid) == -1) {
	error("%s: ncclose failed", pname);
	return;
    }

    if (ncrecinq(ncid, &nrvars, rvarids, rvarsizes) != -1) {
	error("%s: ncrecinq failed to report bad handle", pname);
	nerrs++;
    }

    if (nerrs > 0)
      (void) fprintf(stderr,"FAILED! ***\n");
    else
      (void) fprintf(stderr,"ok ***\n");
}
