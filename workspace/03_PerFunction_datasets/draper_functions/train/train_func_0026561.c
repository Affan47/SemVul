db_create_jobmedia_record(JCR *jcr, B_DB *mdb, JOBMEDIA_DBR *jm)
{
   bool ok = true;
   int count;
   char ed1[50], ed2[50];

   db_lock(mdb);


   Mmsg(mdb->cmd, "SELECT count(*) from JobMedia WHERE JobId=%s",
        edit_int64(jm->JobId, ed1));
   count = get_sql_record_max(jcr, mdb);
   if (count < 0) {
      count = 0;
   }
   count++;

   Mmsg(mdb->cmd,
        "INSERT INTO JobMedia (JobId,MediaId,FirstIndex,LastIndex,"
        "StartFile,EndFile,StartBlock,EndBlock,VolIndex) "
        "VALUES (%s,%s,%u,%u,%u,%u,%u,%u,%u)",
        edit_int64(jm->JobId, ed1),
        edit_int64(jm->MediaId, ed2),
        jm->FirstIndex, jm->LastIndex,
        jm->StartFile, jm->EndFile, jm->StartBlock, jm->EndBlock,count);

   Dmsg0(300, mdb->cmd);
   if (!INSERT_DB(jcr, mdb, mdb->cmd)) {
      Mmsg2(&mdb->errmsg, _("Create JobMedia record %s failed: ERR=%s\n"), mdb->cmd,
         sql_strerror(mdb));
      ok = false;
   } else {

      Mmsg(mdb->cmd,
           "UPDATE Media SET EndFile=%u, EndBlock=%u WHERE MediaId=%u",
           jm->EndFile, jm->EndBlock, jm->MediaId);
      if (!UPDATE_DB(jcr, mdb, mdb->cmd)) {
         Mmsg2(&mdb->errmsg, _("Update Media record %s failed: ERR=%s\n"), mdb->cmd,
              sql_strerror(mdb));
         ok = false;
      }
   }
   db_unlock(mdb);
   Dmsg0(300, "Return from JobMedia\n");
   return ok;
}
