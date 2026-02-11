update_vol_recyclepool(UAContext *ua, char *val, MEDIA_DBR *mr)
{
   POOL_DBR pr;
   POOL_MEM query(PM_MESSAGE);
   char ed1[50], ed2[50], *poolname;

   if(val && *val) {

     memset(&pr, 0, sizeof(pr));
     bstrncpy(pr.Name, val, sizeof(pr.Name));
     if (!get_pool_dbr(ua, &pr, NT_("recyclepool"))) {
        return;
     }

     mr->RecyclePoolId = pr.PoolId;
     poolname = pr.Name;

  } else {

     mr->RecyclePoolId = 0;
     poolname = _("*None*");
  }

   db_lock(ua->db);
   Mmsg(query, "UPDATE Media SET RecyclePoolId=%s WHERE MediaId=%s",
      edit_int64(mr->RecyclePoolId, ed1), edit_int64(mr->MediaId, ed2));
   if (!db_sql_query(ua->db, query.c_str(), NULL, NULL)) {
      ua->error_msg("%s", db_strerror(ua->db));
   } else {
      ua->info_msg(_("New RecyclePool is: %s\n"), poolname);
   }
   db_unlock(ua->db);
}
