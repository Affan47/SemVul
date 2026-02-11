NC4_inq_grps(int ncid, int *numgrps, int *ncids)
{
   NC_GRP_INFO_T *grp, *g;
   NC_HDF5_FILE_INFO_T *h5;
   int num = 0;
   int retval;

   LOG((2, "nc_inq_grps: ncid 0x%x", ncid));


   if ((retval = nc4_find_grp_h5(ncid, &grp, &h5)))
      return retval;


   if (!h5)
   {
      if (numgrps)
         *numgrps = 0;
      return NC_NOERR;
   }


   for (g = grp->children; g; g = g->next)
   {
      if (ncids)
      {


         *ncids = g->nc_grpid | g->file->ext_ncid;
         ncids++;
      }
      num++;
   }

   if (numgrps)
      *numgrps = num;

   return NC_NOERR;
}
