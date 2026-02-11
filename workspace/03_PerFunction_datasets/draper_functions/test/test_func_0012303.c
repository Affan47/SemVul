_show_cursor_cb_change(void *data, Evas_Object *obj __UNUSED__)
{
   E_Config_Dialog_Data *cfdata = data;
   const Eina_List *l;
   Evas_Object *o;

   EINA_LIST_FOREACH(cfdata->disable_list, l, o)
     e_widget_disabled_set(o, !cfdata->show_cursor);

   _use_e_cursor_cb_change(cfdata, NULL);
}
