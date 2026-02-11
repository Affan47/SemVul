plugin_done(void)
{
  if(!claws_is_exiting()) {
    hooks_unregister_hook(ADDDRESS_COMPLETION_BUILD_ADDRESS_LIST_HOOKLIST, hook_address_completion);
    hooks_unregister_hook(OFFLINE_SWITCH_HOOKLIST, hook_offline_switch);
    g_source_remove(timer_query_contacts);
  }
  cm_gdata_prefs_done();
  cm_gdata_contacts_done();

  cm_gdata_save_config();

  debug_print("GData plugin unloaded\n");


  return FALSE;
}
