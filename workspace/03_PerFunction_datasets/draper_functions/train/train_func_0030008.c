starting_up()
{
   u_long32 old_ll = log_state_get_log_level();
   dstring ds;
   dstring ds2 = DSTRING_INIT;
   dstring ds3 = DSTRING_INIT;
   char buffer[256];

   DENTER(TOP_LAYER, "starting_up");

   sge_dstring_init(&ds, buffer, sizeof(buffer));
   log_state_set_log_level(LOG_INFO);

   if (feature_get_active_featureset_id() == FEATURE_NO_SECURITY) {
      sge_dstring_copy_string(&ds2, feature_get_product_name(FS_VERSION, &ds));
   } else {
      sge_dstring_sprintf(&ds2, "%s (%s)",
                          feature_get_product_name(FS_VERSION, &ds),
                          feature_get_featureset_name(
                                       feature_get_active_featureset_id()));
   }
   INFO((SGE_EVENT, MSG_STARTUP_STARTINGUP_SSS,
         feature_get_product_name(FS_SHORT, &ds3),
         sge_dstring_get_string(&ds2), sge_get_arch()));

   sge_dstring_free(&ds2);
   sge_dstring_free(&ds3);
   log_state_set_log_level(old_ll);

   DEXIT;
   return;
}
