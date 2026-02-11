elm_toolbar_item_state_get(const Elm_Object_Item *it)
{
   ELM_OBJ_ITEM_CHECK_OR_RETURN(it, NULL);
   Elm_Toolbar_Item *item = (Elm_Toolbar_Item *)it;

   if ((!item->states) || (!item->current_state)) return NULL;
   if (item->current_state == item->states) return NULL;

   return eina_list_data_get(item->current_state);
}
