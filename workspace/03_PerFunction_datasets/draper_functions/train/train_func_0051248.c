ncclassname(nc_class ncc)
{
    char* s;
    if(ncc >= NC_NAT && ncc <= NC_COMPOUND)
	return nctypename((nc_type)ncc);
    if(ncc == NC_FILLVALUE) return "NC_FILL";
    if(ncc >= NC_GRP && ncc <= NC_PRIM)
	return ncclassnames[ncc - NC_GRP];
    s = poolalloc(128);
    sprintf(s,"NC_<%d>",ncc);
    return s;
}
