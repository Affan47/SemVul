NC_urlmodel(const char* path)
{
    int model = 0;
    NC_URL* tmpurl = NULL;
    struct NCPROTOCOLLIST* protolist;

    if(nc_urlparse(path,&tmpurl) != NC_NOERR) goto done;


    if(nc_urllookup(tmpurl,"netcdf4")
       || nc_urllookup(tmpurl,"netcdf-4")) {
    model = (NC_DISPATCH_NC4|NC_DISPATCH_NCD);
    } else if(nc_urllookup(tmpurl,"netcdf3")
              || nc_urllookup(tmpurl,"netcdf-3")) {
    model = (NC_DISPATCH_NC3|NC_DISPATCH_NCD);
    } else if(nc_urllookup(tmpurl,"cdmremote")
              || nc_urllookup(tmpurl,"cdmr")) {
    model = (NC_DISPATCH_NCR|NC_DISPATCH_NC4);
    }


    for(protolist=ncprotolist;protolist->protocol;protolist++) {
    if(strcmp(tmpurl->protocol,protolist->protocol) == 0) {
    model |= protolist->modelflags;
    if(protolist->substitute)
      nc_urlsetprotocol(tmpurl,protolist->substitute);
    break;
    }
    }

    if((model & NC_DISPATCH_NC4) == 0)
      model |= (NC_DISPATCH_NC3 | NC_DISPATCH_NCD);

done:
    nc_urlfree(tmpurl);
    return model;
}
