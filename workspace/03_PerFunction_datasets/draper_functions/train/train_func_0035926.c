insert_table_into_findex_list(UAContext *ua, RESTORE_CTX *rx, char *table)
{
   strip_trailing_junk(table);
   Mmsg(rx->query, uar_jobid_fileindex_from_table, table);

   rx->found = false;

   if (!db_sql_query(ua->db, rx->query, jobid_fileindex_handler, (void *)rx)) {
      ua->error_msg(_("Query failed: %s. ERR=%s\n"),
         rx->query, db_strerror(ua->db));
   }
   if (!rx->found) {
      ua->error_msg(_("No table found: %s\n"), table);
      return true;
   }
   return true;
}
