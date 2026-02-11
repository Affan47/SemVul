update_volslot(UAContext *ua, char *val, MEDIA_DBR *mr)
{
   POOL_DBR pr;

   memset(&pr, 0, sizeof(POOL_DBR));
   pr.PoolId = mr->PoolId;
   if (!db_get_pool_record(ua->jcr, ua->db, &pr)) {
      ua->error_msg("%s", db_strerror(ua->db));
      return;
   }
   mr->Slot = atoi(val);
   if (pr.MaxVols > 0 && mr->Slot > (int)pr.MaxVols) {
      ua->error_msg(_("Invalid slot, it must be between 0 and MaxVols=%d\n"),
         pr.MaxVols);
      return;
   }


   if (!db_update_media_record(ua->jcr, ua->db, mr)) {
      ua->error_msg(_("Error updating media record Slot: ERR=%s"), db_strerror(ua->db));
   } else {
      ua->info_msg(_("New Slot is: %d\n"), mr->Slot);
   }
}
