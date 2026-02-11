populateLists(int conn)
{
   job_list.clear();
   restore_list.clear();
   client_list.clear();
   fileset_list.clear();
   messages_list.clear();
   pool_list.clear();
   storage_list.clear();
   type_list.clear();
   level_list.clear();
   volstatus_list.clear();
   mediatype_list.clear();
   dir_cmd(conn, ".jobs", job_list);
   dir_cmd(conn, ".jobs type=R", restore_list);
   dir_cmd(conn, ".clients", client_list);
   dir_cmd(conn, ".filesets", fileset_list);
   dir_cmd(conn, ".msgs", messages_list);
   dir_cmd(conn, ".pools", pool_list);
   dir_cmd(conn, ".storage", storage_list);
   dir_cmd(conn, ".types", type_list);
   dir_cmd(conn, ".levels", level_list);
   dir_cmd(conn, ".volstatus", volstatus_list);
   dir_cmd(conn, ".mediatypes", mediatype_list);
   dir_cmd(conn, ".locations", location_list);

   if (mainWin->m_connDebug) {
      QString dbgmsg = QString("jobs=%1 clients=%2 filesets=%3 msgs=%4 pools=%5 storage=%6 types=%7 levels=%8 conn=%9 %10\n")
        .arg(job_list.count()).arg(client_list.count()).arg(fileset_list.count()).arg(messages_list.count())
        .arg(pool_list.count()).arg(storage_list.count()).arg(type_list.count()).arg(level_list.count())
        .arg(conn).arg(m_dir->name());
      Pmsg1(000, "%s", dbgmsg.toUtf8().data());
   }
   job_list.sort();
   client_list.sort();
   fileset_list.sort();
   messages_list.sort();
   pool_list.sort();
   storage_list.sort();
   type_list.sort();
   level_list.sort();
}
