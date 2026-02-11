build_path_hierarchy(JCR *jcr, B_DB *mdb,
                                 pathid_cache &ppathid_cache,
                                 char *org_pathid, char *path)
{
   Dmsg1(dbglevel, "build_path_hierarchy(%s)\n", path);
   char pathid[50];
   ATTR_DBR parent;
   char *bkp = mdb->path;
   strncpy(pathid, org_pathid, sizeof(pathid));


   while (path && *path)
   {
      if (!ppathid_cache.lookup(pathid))
      {
         Mmsg(mdb->cmd,
              "SELECT PPathId FROM PathHierarchy WHERE PathId = %s",
              pathid);

         QUERY_DB(jcr, mdb, mdb->cmd);

         if (sql_num_rows(mdb) > 0) {
            ppathid_cache.insert(pathid);


            goto bail_out;
         } else {

            mdb->path = bvfs_parent_dir(path);
            mdb->pnl = strlen(mdb->path);
            if (!db_create_path_record(jcr, mdb, &parent)) {
               goto bail_out;
            }
            ppathid_cache.insert(pathid);

            Mmsg(mdb->cmd,
                 "INSERT INTO PathHierarchy (PathId, PPathId) "
                 "VALUES (%s,%lld)",
                 pathid, (uint64_t) parent.PathId);

            INSERT_DB(jcr, mdb, mdb->cmd);

            edit_uint64(parent.PathId, pathid);
            path = mdb->path;
         }
      } else {


         goto bail_out;
      }
   }

bail_out:
   mdb->path = bkp;
   mdb->fnl = 0;
}
