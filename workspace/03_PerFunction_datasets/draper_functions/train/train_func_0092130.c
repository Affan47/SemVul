nc_def_var_chunking_ints(int ncid, int varid, int contiguous, int *chunksizesp)
{
   NC_FILE_INFO_T *nc;
   NC_GRP_INFO_T *grp;
   NC_HDF5_FILE_INFO_T *h5;
   NC_VAR_INFO_T *var;
   size_t *cs = NULL;
   int i, retval;


   if ((retval = nc4_find_nc_grp_h5(ncid, &nc, &grp, &h5)))
      return retval;
   assert(nc);


   if (!h5)
      return NC_ENOTNC4;


   if ((retval = nc4_find_g_var_nc(nc, ncid, varid, &grp, &var)))
      return retval;


   if (var->ndims)
      if (!(cs = malloc(var->ndims * sizeof(size_t))))
         return NC_ENOMEM;


   for (i = 0; i < var->ndims; i++)
      cs[i] = chunksizesp[i];

   retval = nc_def_var_extra(ncid, varid, NULL, NULL, NULL, NULL,
                             &contiguous, cs, NULL, NULL, NULL, NULL, NULL);

   if (var->ndims)
      free(cs);
   return retval;
}
