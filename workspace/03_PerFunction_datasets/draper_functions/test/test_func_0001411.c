db_create_path_record(JCR *jcr, B_DB *mdb, ATTR_DBR *ar)
{
   SQL_ROW row;
   int stat;
   int num_rows;

   mdb->esc_name = check_pool_memory_size(mdb->esc_name, 2*mdb->pnl+2);
   db_escape_string(jcr, mdb, mdb->esc_name, mdb->path, mdb->pnl);

   if (mdb->cached_path_id != 0 && mdb->cached_path_len == mdb->pnl &&
       strcmp(mdb->cached_path, mdb->path) == 0) {
      ar->PathId = mdb->cached_path_id;
      return 1;
   }

   Mmsg(mdb->cmd, "SELECT PathId FROM Path WHERE Path='%s'", mdb->esc_name);

   if (QUERY_DB(jcr, mdb, mdb->cmd)) {
      num_rows = sql_num_rows(mdb);
      if (num_rows > 1) {
         char ed1[30];
         Mmsg2(&mdb->errmsg, _("More than one Path!: %s for path: %s\n"),
            edit_uint64(num_rows, ed1), mdb->path);
         Jmsg(jcr, M_WARNING, 0, "%s", mdb->errmsg);
      }

      if (num_rows >= 1) {
         if ((row = sql_fetch_row(mdb)) == NULL) {
            Mmsg1(&mdb->errmsg, _("error fetching row: %s\n"), sql_strerror(mdb));
            Jmsg(jcr, M_ERROR, 0, "%s", mdb->errmsg);
            sql_free_result(mdb);
            ar->PathId = 0;
            ASSERT(ar->PathId);
            return 0;
         }
         ar->PathId = str_to_int64(row[0]);
         sql_free_result(mdb);

         if (ar->PathId != mdb->cached_path_id) {
            mdb->cached_path_id = ar->PathId;
            mdb->cached_path_len = mdb->pnl;
            pm_strcpy(mdb->cached_path, mdb->path);
         }
         ASSERT(ar->PathId);
         return 1;
      }
      sql_free_result(mdb);
   }

   Mmsg(mdb->cmd, "INSERT INTO Path (Path) VALUES ('%s')", mdb->esc_name);

   ar->PathId = sql_insert_autokey_record(mdb, mdb->cmd, NT_("Path"));
   if (ar->PathId == 0) {
      Mmsg2(&mdb->errmsg, _("Create db Path record %s failed. ERR=%s\n"),
         mdb->cmd, sql_strerror(mdb));
      Jmsg(jcr, M_FATAL, 0, "%s", mdb->errmsg);
      ar->PathId = 0;
      stat = 0;
   } else {
      stat = 1;
   }


   if (stat && ar->PathId != mdb->cached_path_id) {
      mdb->cached_path_id = ar->PathId;
      mdb->cached_path_len = mdb->pnl;
      pm_strcpy(mdb->cached_path, mdb->path);
   }
   return stat;
}
