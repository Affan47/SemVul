nc_put_varm_schar(int ncid, int varid,
		  const size_t *start, const size_t *edges,
		  const ptrdiff_t * stride, const ptrdiff_t * imapp,
		  const signed char *value)
{
   NC* ncp;
   int stat = NC_check_id(ncid, &ncp);
   if(stat != NC_NOERR) return stat;
   return NC_put_varm(ncid,varid,start,edges,stride,imapp,(void*)value,NC_BYTE);
}
