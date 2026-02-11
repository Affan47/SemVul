elm_widget_sub_object_del(Evas_Object *obj,
                          Evas_Object *sobj)
{
   Evas_Object *sobj_parent;

   API_ENTRY return EINA_FALSE;
   EINA_SAFETY_ON_TRUE_RETURN_VAL(obj == sobj, EINA_FALSE);

   if (!sobj) return EINA_FALSE;

   if (!sd->api) return EINA_FALSE;
   if (!_elm_legacy_is(obj)) return sd->api->sub_object_del(obj, sobj);


   sobj_parent = evas_object_data_del(sobj, "elm-parent");
   if (sobj_parent != obj)
     {
        static int abort_on_warn = -1;
        ERR("removing sub object %p (%s) from parent %p (%s), "
            "but elm-parent is different %p (%s)!",
            sobj, elm_widget_type_get(sobj), obj, elm_widget_type_get(obj),
            sobj_parent, elm_widget_type_get(sobj_parent));
        if (EINA_UNLIKELY(abort_on_warn == -1))
          {
             if (getenv("ELM_ERROR_ABORT")) abort_on_warn = 1;
             else abort_on_warn = 0;
          }
        if (abort_on_warn == 1) abort();

        return EINA_FALSE;
     }
   if (_elm_widget_is(sobj))
     {
        if (elm_widget_focus_get(sobj))
          {
             elm_widget_tree_unfocusable_set(sobj, EINA_TRUE);
             elm_widget_tree_unfocusable_set(sobj, EINA_FALSE);
          }
        if ((sd->child_can_focus) && (_is_focusable(sobj)))
          {
             Evas_Object *subobj;
             const Eina_List *l;
             Elm_Widget_Smart_Data *sdt = evas_object_smart_data_get(obj);
             while (1)
               {
                  sdt->child_can_focus = EINA_FALSE;
                  EINA_LIST_FOREACH(sdt->subobjs, l, subobj)
                    {
                       if ((subobj != sobj) && (_is_focusable(subobj)))
                         {
                            sdt->child_can_focus = EINA_TRUE;
                            break;
                         }
                    }
                  if (sdt->child_can_focus) break;
                  if (!sdt->parent_obj) break;
                  sdt = evas_object_smart_data_get(sdt->parent_obj);
               }
          }
        Elm_Widget_Smart_Data *sd2 = evas_object_smart_data_get(sobj);
        if (sd2)
          {
             sd2->parent_obj = NULL;
              if (sd2->resize_obj == sobj) sd2->resize_obj = NULL;

              sd->subobjs = eina_list_remove(sd->subobjs, sobj);
          }
        else
          sd->subobjs = eina_list_remove(sd->subobjs, sobj);
     }
   else
     sd->subobjs = eina_list_remove(sd->subobjs, sobj);
   evas_object_event_callback_del_full(sobj, EVAS_CALLBACK_DEL,
                                       _sub_obj_del, sd);
   if (_elm_widget_is(sobj))
     evas_object_event_callback_del_full(sobj, EVAS_CALLBACK_HIDE,
                                         _sub_obj_hide, sd);
   evas_object_smart_callback_call(obj, "sub-object-del", sobj);

   return EINA_TRUE;
}
