gdata_save_prefs(PrefsPage *page)
{
  int old_max_cache_age = cm_gdata_config.max_cache_age;

  if (!page->page_open)
    return;

  prefs_set_data_from_dialog(cm_gdata_param);

  cm_gdata_update_contacts_cache();
  if(old_max_cache_age != cm_gdata_config.max_cache_age)
    cm_gdata_update_contacts_update_timer();
}
