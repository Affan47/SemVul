spool_berkeleydb_default_startup_func(lList **answer_list,
                                      const lListElem *rule, bool check)
{
   bool ret = true;
   bdb_info info;

   DENTER(BDB_LAYER, "spool_berkeleydb_default_startup_func");

   info = (bdb_info)lGetRef(rule, SPR_clientdata);

   ret = spool_berkeleydb_check_version(answer_list);

   if (ret) {
      ret = spool_berkeleydb_create_environment(answer_list, info);
   }


   if (ret && check) {
      ret = spool_berkeleydb_open_database(answer_list, info, false);
   }

   DEXIT;
   return ret;
}
