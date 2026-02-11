nc4_enddef_netcdf4_file(NC_HDF5_FILE_INFO_T *h5)
{
   assert(h5);
   LOG((3, "nc4_enddef_netcdf4_file"));


   if (!(h5->flags & NC_INDEF))
      return NC_ENOTINDEFINE;


   h5->flags ^= NC_INDEF;


   h5->redef = 0;

   return sync_netcdf4_file(h5);
}
