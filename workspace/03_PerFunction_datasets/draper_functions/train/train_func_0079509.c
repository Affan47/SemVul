check_for_vara(nc_type *mem_nc_type, NC_VAR_INFO_T *var, NC_HDF5_FILE_INFO_T *h5)
{
   int retval;


   assert(mem_nc_type);
   if (*mem_nc_type == NC_NAT)
      *mem_nc_type = var->xtype;
   assert(*mem_nc_type);


   if (var->xtype != *mem_nc_type &&
       (var->xtype == NC_CHAR || *mem_nc_type == NC_CHAR))
      return NC_ECHAR;


   if (h5->flags & NC_INDEF)
   {
      if (h5->cmode & NC_CLASSIC_MODEL)
         return NC_EINDEFINE;
      if ((retval = nc4_enddef_netcdf4_file(h5)))
         return retval;
   }

   return NC_NOERR;
}
