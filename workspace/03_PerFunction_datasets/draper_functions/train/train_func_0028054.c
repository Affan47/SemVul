nc_inq_grpname_full(int ncid, size_t *lenp, char *full_name)
{
    NC* ncp;
    int stat = NC_check_id(ncid,&ncp);
    if(stat != NC_NOERR) return stat;
    return ncp->dispatch->inq_grpname_full(ncid,lenp,full_name);
}
