nc4_put_att_tc(int ncid, int varid, const char *name, nc_type file_type,
               nc_type mem_type, int mem_type_is_long, size_t len,
               const void *op)
{
   NC_FILE_INFO_T *nc;

   if (!name || strlen(name) > NC_MAX_NAME)
      return NC_EBADNAME;

   LOG((3, "nc4_put_att_tc: ncid 0x%x varid %d name %s file_type %d "
        "mem_type %d len %d", ncid, varid, name, file_type, mem_type, len));


   if((unsigned long) len > X_INT_MAX)
      return NC_EINVAL;


   if (!(nc = nc4_find_nc_file(ncid)))
      return NC_EBADID;

#ifdef USE_PNETCDF

   if (nc->pnetcdf_file)
   {
      if (mem_type == NC_UBYTE)
         mem_type = NC_BYTE;
      switch(mem_type)
      {
         case NC_BYTE:
            return ncmpi_put_att_schar(nc->int_ncid, varid, name,
                                     file_type, len, op);
         case NC_CHAR:
            return ncmpi_put_att_text(nc->int_ncid, varid, name,
                                    len, op);
         case NC_SHORT:
            return ncmpi_put_att_short(nc->int_ncid, varid, name,
                                     file_type, len, op);
         case NC_INT:
            if (mem_type_is_long)
               return ncmpi_put_att_long(nc->int_ncid, varid, name,
                                       file_type, len, op);
            else
               return ncmpi_put_att_int(nc->int_ncid, varid, name,
                                      file_type, len, op);
         case NC_FLOAT:
            return ncmpi_put_att_float(nc->int_ncid, varid, name,
                                     file_type, len, op);
         case NC_DOUBLE:
            return ncmpi_put_att_double(nc->int_ncid, varid, name,
                                      file_type, len, op);
         case NC_NAT:
         default:
            return NC_EBADTYPE;
      }
   }
#endif


   assert(nc->nc4_info);


   return nc4_put_att(ncid, nc, varid, name, file_type, mem_type, len,
                      mem_type_is_long, op);
}
