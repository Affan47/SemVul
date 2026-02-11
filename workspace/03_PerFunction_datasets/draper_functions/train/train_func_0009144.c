elm_naviframe_item_insert_before(Evas_Object *obj,
                                 Elm_Object_Item *before,
                                 const char *title_label,
                                 Evas_Object *prev_btn,
                                 Evas_Object *next_btn,
                                 Evas_Object *content,
                                 const char *item_style)
{
   Elm_Naviframe_Item *it, *prev_it;

   ELM_NAVIFRAME_CHECK(obj) NULL;
   ELM_NAVIFRAME_ITEM_CHECK_OR_RETURN(before, NULL);
   ELM_NAVIFRAME_DATA_GET(obj, sd);

   prev_it = NULL;
   if (before)
     {
        it = (Elm_Naviframe_Item *)before;
        prev_it = EINA_INLIST_CONTAINER_GET(EINA_INLIST_GET(it)->prev,
                                            Elm_Naviframe_Item);
     }

   it = _item_new(obj, prev_it,
                  title_label, prev_btn, next_btn, content, item_style);
   if (!it) return NULL;
   elm_widget_resize_object_set(obj, VIEW(it));
   evas_object_smart_member_add(sd->dummy_edje, obj);

   sd->stack = eina_inlist_prepend_relative
       (sd->stack, EINA_INLIST_GET(it),
       EINA_INLIST_GET(((Elm_Naviframe_Item *)before)));

   elm_layout_sizing_eval(obj);

   return (Elm_Object_Item *)it;
}
