elm_toolbar_item_state_next(Elm_Object_Item *it)
{
   ELM_OBJ_ITEM_CHECK_OR_RETURN(it, NULL);

   Widget_Data *wd;
   Evas_Object *obj;
   Eina_List *next_state;
   Elm_Toolbar_Item *item = (Elm_Toolbar_Item *)it;

   obj = WIDGET(item);
   wd = elm_widget_data_get(obj);
   if (!wd) return NULL;
   if (!item->states) return NULL;

   next_state = eina_list_next(item->current_state);
   if (!next_state)
     next_state = eina_list_next(item->states);
   return eina_list_data_get(next_state);
}
