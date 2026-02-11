ts_change(void *data       __UNUSED__,
          Evas_Object     *obj,
          void *event_info __UNUSED__)
{
   Eina_Bool val = elm_check_state_get(obj);
   Eina_Bool sb = elm_config_scroll_thumbscroll_enabled_get();

   if (val == sb) return;
   elm_config_scroll_thumbscroll_enabled_set(val);
   elm_config_all_flush();


}
