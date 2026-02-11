test_ncopen(path)
     char *path;
{
    int nerrs = 0;
    static char pname[] = "test_ncopen";
    int cdfid0, cdfid1;
    static char title_val[] = "test netcdf";
    static char xpath[] = "tooth-fairy.cdf";
    static struct cdfatt title =
      {NC_GLOBAL, "title", NC_CHAR, LEN_OF (title_val), (void *) title_val};

    (void) fprintf(stderr, "*** Testing %s ...\t\t", &pname[5]);

    if((cdfid0 = ncopen(xpath, NC_NOWRITE)) != -1) {
	error("%s: ncopen should fail opening nonexistent file",
	      pname);
	return;
    }
    if((cdfid0 = ncopen(xpath, NC_WRITE)) != -1) {
	error("%s: ncopen should fail writing nonexistent file",
	      pname);
	return;
    }
    if ((cdfid0 = ncopen(path, NC_WRITE)) == -1) {
	error("%s: ncopen failed with NC_WRITE mode", pname);
	return;
    }

    if (ncredef(cdfid0) == -1) {
	error("%s: cdredef failed", pname);
	ncclose(cdfid0); return;
    }

    if (ncattput(cdfid0, NC_GLOBAL, "title", NC_CHAR, title.len, title.val)
	== -1) {
	error("%s: ncattput failed", pname);
	ncclose(cdfid0); return;
    }
    add_att(&test, NC_GLOBAL, &title);
    if (ncendef (cdfid0) == -1) {
	error("%s: ncendef failed after ncattput", pname);
	ncclose(cdfid0); return;
    }
    if (ncclose (cdfid0) == -1) {
	error("%s: ncclose failed in NC_WRITE mode", pname);
	return;
    }

    if ((cdfid0 = ncopen(path, NC_NOWRITE)) == -1) {
	error("%s: ncopen failed with NC_NOWRITE mode", pname);
	return;
    }


    if (ncredef(cdfid0) != -1) {
	error("%s: cdredef should fail after NC_NOWRITE open", pname);
	ncclose(cdfid0); return;
    }

    if ((cdfid1 = ncopen(path, NC_WRITE)) == -1) {
	error("%s: second ncopen failed", pname);
	nerrs++;
    }
    else
    {

	    if (cdfid0 == cdfid1) {
		error("%s: ncopen should return new cdfid on second open",
		      pname);
		nerrs++;
	    }
	    if (ncclose (cdfid1) == -1) {
		error("%s: ncclose failed to close after second open", pname);
		nerrs++;
	    }
    }

    if (ncclose (cdfid0) == -1) {
	error("%s: ncclose failed in NC_NOWRITE mode", pname);
	nerrs++;
    }
    if (nerrs > 0)
      (void) fprintf(stderr,"FAILED! ***\n");
    else
      (void) fprintf(stderr,"ok ***\n");
}
