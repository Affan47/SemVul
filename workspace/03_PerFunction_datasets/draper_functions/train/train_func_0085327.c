defseqdims(NCDAP3* drno)
{
    unsigned int i;
    CDFnode* unlimited = NULL;
    NCerror ncstat = NC_NOERR;
    int seqdims = 1;


    if(paramcheck34(&drno->dap,"show","seqdims")) seqdims = 0;


    if(!FLAGSET(drno->dap.controls,NCF_NOUNLIM)) {
        unlimited = makecdfnode34(&drno->dap,"unlimited",OC_Dimension,OCNULL,drno->dap.cdf.ddsroot);
        nclistpush(drno->dap.cdf.ddsroot->tree->nodes,(ncelem)unlimited);
        nullfree(unlimited->ncbasename);
        nullfree(unlimited->ncfullname);
        unlimited->ncbasename = cdflegalname3(unlimited->name);
        unlimited->ncfullname = nulldup(unlimited->ncbasename);
        DIMFLAGSET(unlimited,CDFDIMUNLIM);
        drno->dap.cdf.unlimited = unlimited;
    }


    for(i=0;i<nclistlength(drno->dap.cdf.seqnodes);i++) {
        CDFnode* seq = (CDFnode*)nclistget(drno->dap.cdf.seqnodes,i);
	CDFnode* sqdim;
	size_t seqsize;

        seq->array.dimensions = nclistnew();

	if(!seq->usesequence) {

	    seq->array.seqdim = unlimited;
	    nclistpush(seq->array.dimensions,(ncelem)unlimited);
	    continue;
	}


	sqdim = NULL;
	if(seqdims) {
	    ncstat = getseqdimsize(&drno->dap,seq,&seqsize);
	    if(ncstat != NC_NOERR) {

		sqdim = unlimited;
	    }
	} else {
	    seqsize = 1;
	}
	if(sqdim == NULL) {

            ncstat = makeseqdim(&drno->dap,seq,seqsize,&sqdim);
            if(ncstat) goto fail;
	}
        seq->array.seqdim = sqdim;
	nclistpush(seq->array.dimensions,(ncelem)sqdim);
    }

fail:
    return ncstat;
}
