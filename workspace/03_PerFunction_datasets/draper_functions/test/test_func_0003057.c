_basic_check_changed(E_Config_Dialog *cfd __UNUSED__, E_Config_Dialog_Data *cfdata)
{
   Eina_Bool ret;
   int old_show_alert = ((battery_config->alert > 0) ||
                         (battery_config->alert_p > 0));

   ret = (cfdata->show_alert != old_show_alert);
#ifdef HAVE_ENOTIFY
   ret |= (cfdata->desktop_notifications != battery_config->desktop_notifications);
#endif
   return ret;
}
