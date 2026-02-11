nc4_reopen_dataset(NC_GRP_INFO_T *grp, NC_VAR_INFO_T *var)
{
   hid_t access_pid;

   if (var->hdf_datasetid)
   {
      if ((access_pid = H5Pcreate(H5P_DATASET_ACCESS)) < 0)
         return NC_EHDFERR;
#ifdef EXTRA_TESTS
      num_plists++;
#endif
      if (H5Pset_chunk_cache(access_pid, var->chunk_cache_nelems,
                             var->chunk_cache_size,
                             var->chunk_cache_preemption) < 0)
         return NC_EHDFERR;
      if (H5Dclose(var->hdf_datasetid) < 0)
         return NC_EHDFERR;
      if ((var->hdf_datasetid = H5Dopen2(grp->hdf_grpid, var->name,
                                         access_pid)) < 0)
         return NC_EHDFERR;
      if (H5Pclose(access_pid) < 0)
         return NC_EHDFERR;
#ifdef EXTRA_TESTS
      num_plists--;
#endif

      if (var->dimscale)
         var->dim[0]->hdf_dimscaleid = var->hdf_datasetid;
   }

   return NC_NOERR;
}
