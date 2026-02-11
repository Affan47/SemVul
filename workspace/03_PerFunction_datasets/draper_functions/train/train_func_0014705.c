_elm_list_smart_focus_next(const Evas_Object *obj,
                           Elm_Focus_Direction dir,
                           Evas_Object **next)
{
   Eina_List *items = NULL;
   Eina_List *elist = NULL;
   Elm_List_Item *it;

   ELM_LIST_CHECK(obj) EINA_FALSE;
   ELM_LIST_DATA_GET(obj, sd);

   if (_elm_config->access_mode != ELM_ACCESS_MODE_ON) return EINA_FALSE;

   EINA_LIST_FOREACH (sd->items, elist, it)
     {
        items = eina_list_append(items, it->base.access_obj);
        if (it->icon) items = eina_list_append(items, it->icon);
        if (it->end) items = eina_list_append(items, it->end);
     }

   return elm_widget_focus_list_next_get
            (obj, items, eina_list_data_get, dir, next);
}
