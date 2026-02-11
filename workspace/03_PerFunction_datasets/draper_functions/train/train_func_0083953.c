elm_toolbar_item_icon_file_set(Elm_Object_Item *it, const char *file, const char *key)
{
   ELM_OBJ_ITEM_CHECK_OR_RETURN(it, EINA_FALSE);

   Evas_Object *icon_obj;
   Widget_Data *wd;
   Evas_Object *obj;
   Eina_Bool ret;
   Elm_Toolbar_Item *item = (Elm_Toolbar_Item *)it;

   obj = WIDGET(item);
   wd = elm_widget_data_get(obj);
   if (!wd) return EINA_FALSE;

   if (file)
     {
        icon_obj = elm_icon_add(obj);
        evas_object_repeat_events_set(icon_obj, EINA_TRUE);
        ret = elm_image_file_set(icon_obj, file, key);
        if (!ret)
          {
             evas_object_del(icon_obj);
             return EINA_FALSE;
          }
        _elm_toolbar_item_icon_obj_set(obj, item, icon_obj, NULL, wd->icon_size,
                                         "elm,state,icon_set");
     }
   else
     _elm_toolbar_item_icon_obj_set(obj, item, NULL, NULL, 0, "elm,state,icon_set");
   return EINA_TRUE;
}
