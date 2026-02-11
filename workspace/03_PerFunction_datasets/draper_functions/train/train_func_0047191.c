_smart_del(Evas_Object *obj)
{
   Evas_Object *sobj;
   Elm_Translate_String_Data *ts;
   Elm_Event_Cb_Data *ecb;

   ELM_WIDGET_DATA_GET(obj, sd);

   if (sd->hover_obj)
     {

        evas_object_event_callback_del_full
          (sd->hover_obj, EVAS_CALLBACK_DEL, _sub_obj_del, sd);
        sd->hover_obj = NULL;
     }

   while (sd->subobjs)
     {
        sobj = eina_list_data_get(sd->subobjs);


        if (_elm_legacy_is(sd->obj))
          {
             evas_object_smart_callback_call(obj, "sub-object-del", sobj);
             sd->subobjs = eina_list_remove_list(sd->subobjs, sd->subobjs);
          }
        else
          {
             if (!elm_widget_sub_object_del(obj, sobj))
               {
                  ERR("failed to remove sub object %p from %p\n", sobj, obj);
                  sd->subobjs = eina_list_remove_list
                      (sd->subobjs, sd->subobjs);
               }
          }
        evas_object_del(sobj);
     }
   sd->tooltips = eina_list_free(sd->tooltips);
   sd->cursors = eina_list_free(sd->cursors);
   EINA_LIST_FREE(sd->translate_strings, ts)
     {
        eina_stringshare_del(ts->id);
        eina_stringshare_del(ts->domain);
        eina_stringshare_del(ts->string);
        free(ts);
     }

   EINA_LIST_FREE(sd->event_cb, ecb)
         free(ecb);

   if (sd->style) eina_stringshare_del(sd->style);
   if (sd->theme) elm_theme_free(sd->theme);
   _if_focused_revert(obj, EINA_TRUE);
   if (sd->access_info) eina_stringshare_del(sd->access_info);
   free(sd);
   evas_object_smart_data_set(obj, NULL);
}
