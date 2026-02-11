prune_set_filter(UAContext *ua, CLIENT *client, POOL *pool, utime_t period,
                      POOL_MEM *add_from, POOL_MEM *add_where)
{
   utime_t now;
   char ed1[50], ed2[MAX_ESCAPE_NAME_LENGTH];
   POOL_MEM tmp(PM_MESSAGE);

   now = (utime_t)time(NULL);
   edit_int64(now - period, ed1);
   Dmsg3(150, "now=%lld period=%lld JobTDate=%s\n", now, period, ed1);
   Mmsg(tmp, " AND JobTDate < %s ", ed1);
   pm_strcat(*add_where, tmp.c_str());

   db_lock(ua->db);
   if (client) {
      db_escape_string(ua->jcr, ua->db, ed2,
                       client->name(), strlen(client->name()));
      Mmsg(tmp, " AND Client.Name = '%s' ", ed2);
      pm_strcat(*add_where, tmp.c_str());
      pm_strcat(*add_from, " JOIN Client USING (ClientId) ");
   }

   if (pool) {
      db_escape_string(ua->jcr, ua->db, ed2,
                       pool->name(), strlen(pool->name()));
      Mmsg(tmp, " AND Pool.Name = '%s' ", ed2);
      pm_strcat(*add_where, tmp.c_str());

      pm_strcat(*add_from, " JOIN Pool ON (Job.PoolId = Pool.PoolId) ");
   }
   Dmsg2(150, "f=%s w=%s\n", add_from->c_str(), add_where->c_str());
   db_unlock(ua->db);
   return true;
}
