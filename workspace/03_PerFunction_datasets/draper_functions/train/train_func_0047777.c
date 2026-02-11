_item_del_pre_hook(Elm_Object_Item *it)
{
   Evas_Object *list;
   Widget_Data *wd;
   Elm_Ctxpopup_Item *ctxpopup_it = (Elm_Ctxpopup_Item *)it;

   wd = elm_widget_data_get(WIDGET(ctxpopup_it));
   if (!wd) return EINA_FALSE;

   wd->dir = ELM_CTXPOPUP_DIRECTION_UNKNOWN;

   list = elm_object_item_widget_get(ctxpopup_it->list_item);

   if (eina_list_count(elm_list_items_get(list)) < 2)
     {
        elm_object_item_del(ctxpopup_it->list_item);
        wd->items = eina_list_remove(wd->items, it);
        evas_object_hide(WIDGET(ctxpopup_it));
        return EINA_TRUE;
     }

   elm_object_item_del(ctxpopup_it->list_item);
   wd->items = eina_list_remove(wd->items, it);
   if (wd->list_visible)
     _sizing_eval(WIDGET(ctxpopup_it));

   return EINA_TRUE;
}
