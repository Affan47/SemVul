_elm_diskselector_smart_focus_next(const Evas_Object *obj,
                           Elm_Focus_Direction dir,
                           Evas_Object **next)
{
   Eina_List *items = NULL;
   Eina_List *elist = NULL;
   Elm_Diskselector_Item *it;

   ELM_DISKSELECTOR_CHECK(obj) EINA_FALSE;
   ELM_DISKSELECTOR_DATA_GET(obj, sd);

   EINA_LIST_FOREACH (sd->items, elist, it)
     items = eina_list_append(items, it->base.access_obj);

   if (!sd->round)
     return elm_widget_focus_list_next_get
              (obj, items, eina_list_data_get, dir, next);

   if (!elm_widget_focus_list_next_get
          (obj, items, eina_list_data_get, dir, next))
     {
        elm_widget_focused_object_clear((Evas_Object *)obj);
        elm_widget_focus_list_next_get
          (obj, items, eina_list_data_get, dir, next);
     }
   return EINA_TRUE;
}
