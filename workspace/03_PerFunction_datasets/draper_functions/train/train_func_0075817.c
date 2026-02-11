nc_put_att_string(int ncid, int varid, const char *name,
		  size_t len, const char** value)
{
    NC* ncp;
    int stat = NC_check_id(ncid, &ncp);
    if(stat != NC_NOERR) return stat;
    return ncp->dispatch->put_att(ncid,varid,name,NC_STRING,len,(void*)value,NC_STRING);
}
