e_fm2_refresh(Evas_Object *obj)
{
   EFM_SMART_CHECK();

   _e_fm2_dir_save_props(sd);

   _e_fm2_queue_free(obj);
   _e_fm2_regions_free(obj);
   _e_fm2_icons_free(obj);

   sd->order_file = EINA_FALSE;

   if (sd->realpath)
     {
        sd->listing = EINA_FALSE;
        _e_fm2_client_monitor_del(sd->id, sd->realpath);
        sd->id = _e_fm2_client_monitor_add(sd->realpath);
        sd->listing = EINA_TRUE;
     }

   sd->tmp.iter = EINA_FALSE;
}
