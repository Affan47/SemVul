_access_obj_over_timeout_cb(void *data)
{
   Elm_Access_Info *ac = evas_object_data_get(data, "_elm_access");
   if (!ac) return EINA_FALSE;
   if (_elm_config->access_mode != ELM_ACCESS_MODE_OFF)
     {
        if (ac->on_highlight) ac->on_highlight(ac->on_highlight_data);
        _elm_access_object_hilight(data);
        _elm_access_read(ac, ELM_ACCESS_CANCEL, data, NULL);
        _elm_access_read(ac, ELM_ACCESS_TYPE,   data, NULL);
        _elm_access_read(ac, ELM_ACCESS_INFO,   data, NULL);
        _elm_access_read(ac, ELM_ACCESS_STATE,  data, NULL);
        _elm_access_read(ac, ELM_ACCESS_DONE,   data, NULL);
     }
   ac->delay_timer = NULL;
   return EINA_FALSE;
}
