elm_flipselector_item_prev_get(const Elm_Object_Item *it)
{
   Elm_Flipselector_Item *item = (Elm_Flipselector_Item *)it;
   Eina_List *l;

   ELM_FLIPSELECTOR_ITEM_CHECK_OR_RETURN(it, NULL);
   ELM_FLIPSELECTOR_DATA_GET(WIDGET(item), sd);

   if ((!sd->items)) return NULL;

   l = eina_list_data_find_list(sd->items, it);
   if (l && l->prev) return DATA_GET(l->prev);

   return NULL;
}
