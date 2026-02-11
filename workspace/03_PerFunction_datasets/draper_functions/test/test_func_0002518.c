nc_get_vara_ubyte(int ncid, int varid,
		  const size_t *start, const size_t *edges, unsigned char *value)
{
   NC* ncp;
   int stat = NC_check_id(ncid, &ncp);
   if(stat != NC_NOERR) return stat;
   return NC_get_vara(ncid,varid,start,edges,(void*)value,T_ubyte);
}
