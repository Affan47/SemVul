_basic_check_changed(E_Config_Dialog *cfd __UNUSED__, E_Config_Dialog_Data *cfdata)
{
   if (cfdata->framerate <= 0.0) cfdata->framerate = 1.0;
   return ((e_config->framerate != cfdata->framerate) ||
	   (e_config->cache_flush_poll_interval != cfdata->cache_flush_poll_interval) ||
	   (e_config->font_cache != (cfdata->font_cache * 1024)) ||
	   (e_config->image_cache != (cfdata->image_cache * 1024)) ||
	   (e_config->edje_cache != cfdata->edje_cache) ||
	   (e_config->edje_collection_cache != cfdata->edje_collection_cache) ||
	   (e_config->priority != cfdata->priority) ||
           (e_config->no_module_delay != (!cfdata->module_delay)));
}
