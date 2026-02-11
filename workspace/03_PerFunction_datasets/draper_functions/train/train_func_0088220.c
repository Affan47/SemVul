_cb_disable(void *data, Evas_Object *obj __UNUSED__)
{
   E_Config_Dialog_Data *cfdata;
   const Eina_List *l;
   Evas_Object *o;

   if (!(cfdata = data)) return;
   EINA_LIST_FOREACH(cfdata->disable_list, l, o)
     e_widget_disabled_set(o, !cfdata->enable_screensaver);

   _cb_ask_presentation_changed(cfdata, NULL);
}
