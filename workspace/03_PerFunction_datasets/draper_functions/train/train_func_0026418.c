_fill_data(E_Config_Dialog_Data *cfdata)
{
   Eina_List *l;
   E_Config_Desklock_Background *bg;
   int x;

   cfdata->zone_count = _zone_count_get();
   EINA_LIST_FOREACH(e_config->desklock_backgrounds, l, bg)
     cfdata->bgs = eina_list_append(cfdata->bgs, eina_stringshare_ref(bg->file));
   if (!cfdata->bgs)
     for (x = 0; x < cfdata->zone_count; x++)
     cfdata->bgs = eina_list_append(cfdata->bgs, eina_stringshare_add("theme_desklock_background"));

   if (!e_util_strcmp(eina_list_data_get(cfdata->bgs), "theme_desklock_background"))
     cfdata->bg_method = E_DESKLOCK_BACKGROUND_METHOD_THEME_DESKLOCK;
   else if (!e_util_strcmp(eina_list_data_get(cfdata->bgs), "theme_background"))
     cfdata->bg_method = E_DESKLOCK_BACKGROUND_METHOD_THEME;
   else if (!e_util_strcmp(eina_list_data_get(cfdata->bgs), "user_background"))
     cfdata->bg_method = E_DESKLOCK_BACKGROUND_METHOD_WALLPAPER;
   else
     cfdata->bg_method = E_DESKLOCK_BACKGROUND_METHOD_CUSTOM;

   cfdata->bg_method_prev = cfdata->bg_method;
   cfdata->use_xscreensaver = ecore_x_screensaver_event_available_get();

   cfdata->custom_lock = e_config->desklock_use_custom_desklock;
   if (e_config->desklock_custom_desklock_cmd)
     cfdata->custom_lock_cmd = strdup(e_config->desklock_custom_desklock_cmd);

   cfdata->desklock_layout = e_config->xkb.desklock_layout;
   cfdata->start_locked = e_config->desklock_start_locked;
   cfdata->lock_on_suspend = e_config->desklock_on_suspend;
   cfdata->auto_lock = e_config->desklock_autolock_idle;
   cfdata->screensaver_lock = e_config->desklock_autolock_screensaver;
   cfdata->idle_time = e_config->desklock_autolock_idle_timeout / 60;
   cfdata->post_screensaver_time = e_config->desklock_post_screensaver_time;
   if (e_config->desklock_login_box_zone >= 0)
     {
        cfdata->login_zone = 0;
        cfdata->zone = e_config->desklock_login_box_zone;
     }
   else
     {
        cfdata->login_zone = e_config->desklock_login_box_zone;
        cfdata->zone = 0;
     }

   cfdata->ask_presentation = e_config->desklock_ask_presentation;
   cfdata->ask_presentation_timeout =
     e_config->desklock_ask_presentation_timeout;
}
