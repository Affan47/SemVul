prune_volume(UAContext *ua, MEDIA_DBR *mr)
{
   POOL_MEM query(PM_MESSAGE);
   struct del_ctx del;
   bool ok = false;
   int count;

   if (mr->Enabled == 2) {
      return false;
   }

   memset(&del, 0, sizeof(del));
   del.max_ids = 10000;
   del.JobId = (JobId_t *)malloc(sizeof(JobId_t) * del.max_ids);

   db_lock(ua->db);


   if (strcmp(mr->VolStatus, "Full")   == 0 ||
       strcmp(mr->VolStatus, "Used")   == 0) {
      Dmsg2(050, "get prune list MediaId=%d Volume %s\n", (int)mr->MediaId, mr->VolumeName);
      count = get_prune_list_for_volume(ua, mr, &del);
      Dmsg1(050, "Num pruned = %d\n", count);
      if (count != 0) {
         purge_job_list_from_catalog(ua, del);
      }
      ok = is_volume_purged(ua, mr);
   }

   db_unlock(ua->db);
   if (del.JobId) {
      free(del.JobId);
   }
   return ok;
}
