fetchtemplatemetadata3(NCDAPCOMMON* nccomm)
{
    NCerror ncstat = NC_NOERR;
    OCerror ocstat = OC_NOERR;
    OCobject ocroot = OCNULL;
    CDFnode* ddsroot = NULL;
    char* ce = NULL;


    if(FLAGSET(nccomm->controls,NCF_UNCONSTRAINABLE))
	ce = NULL;
    else
        ce = nulldup(nccomm->oc.uri->selection);


    ocstat = dap_oc_fetch(nccomm,nccomm->oc.conn,ce,OCDDS,&ocroot);
    if(ocstat != OC_NOERR) {


	if(strcmp(nccomm->oc.uri->protocol,"file") != 0) {
	    THROWCHK(ocstat); goto done;
	}

        ocstat = dap_oc_fetch(nccomm,nccomm->oc.conn,ce,OCDATADDS,&ocroot);
        if(ocstat != OC_NOERR) {
	    THROWCHK(ocstat); goto done;
	}

	nclog(NCLOGWARN,"Cannot locate .dds file, using .dods file");
    }


    if(nccomm->oc.ocdasroot != OCNULL)
	oc_root_free(nccomm->oc.conn,nccomm->oc.ocdasroot);
    nccomm->oc.ocdasroot = OCNULL;
    ocstat = dap_oc_fetch(nccomm,nccomm->oc.conn,ce,OCDAS,&nccomm->oc.ocdasroot);
    if(ocstat != OC_NOERR) {

	nclog(NCLOGWARN,"Could not read DAS; ignored");
        nccomm->oc.ocdasroot = OCNULL;
	ocstat = OC_NOERR;
    }


    ncstat = buildcdftree34(nccomm,ocroot,OCDDS,&ddsroot);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}
#ifdef IGNORE
    if(nccomm->cdf.ddsroot != NULL)
	freecdfroot34(&drno->dap->cdf.ddsroot);
#endif
    nccomm->cdf.ddsroot = ddsroot;


    ncstat = dapmerge3(nccomm,ddsroot,nccomm->oc.ocdasroot);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}

done:
    nullfree(ce);
    if(ocstat != OC_NOERR) ncstat = ocerrtoncerr(ocstat);
    return ncstat;
}
