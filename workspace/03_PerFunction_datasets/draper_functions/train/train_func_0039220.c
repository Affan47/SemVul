computevarnodes3(NCDAPCOMMON* nccomm, NClist* allnodes, NClist* varnodes)
{
    unsigned int i,len;
    NClist* allvarnodes = nclistnew();
    for(i=0;i<nclistlength(allnodes);i++) {
	CDFnode* node = (CDFnode*)nclistget(allnodes,i);

	if(dap_badname(node->name)) node->visible=0;
	if(!node->visible) continue;
	if(node->nctype == NC_Primitive)
	    nclistpush(allvarnodes,(ncelem)node);
    }


    len = nclistlength(allvarnodes);
    for(i=0;i<len;i++) {
	CDFnode* node = (CDFnode*)nclistget(allvarnodes,i);
	if(node == NULL) continue;
        if(daptoplevel(node)) {
	    nclistpush(varnodes,(ncelem)node);
	    nclistset(allvarnodes,i,(ncelem)NULL);
	}
    }


    for(i=0;i<len;i++) {
	CDFnode* node = (CDFnode*)nclistget(allvarnodes,i);
	if(node == NULL) continue;
	if(dapgridarray(node)) {
	    nclistpush(varnodes,(ncelem)node);
	    nclistset(allvarnodes,i,(ncelem)NULL);
        } else if(dapgridmap(node)) {
	    if(!FLAGSET(nccomm->controls,NCF_NCDAP))
		nclistpush(varnodes,(ncelem)node);
	    nclistset(allvarnodes,i,(ncelem)NULL);
	}
    }

    for(i=0;i<len;i++) {
	CDFnode* node = (CDFnode*)nclistget(allvarnodes,i);
	if(node == NULL) continue;
        nclistpush(varnodes,(ncelem)node);
    }
    nclistfree(allvarnodes);
    return NC_NOERR;
}
