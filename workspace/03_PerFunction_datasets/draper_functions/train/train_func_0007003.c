_round_items_del(Elm_Diskselector_Smart_Data *sd)
{
   Eina_List *l;
   Elm_Diskselector_Item *it;

   _round_item_del(sd, sd->last);
   sd->last = NULL;
   _round_item_del(sd, sd->s_last);
   sd->s_last = NULL;
   _round_item_del(sd, sd->second);
   sd->second = NULL;
   _round_item_del(sd, sd->first);
   sd->first = NULL;

   EINA_LIST_FOREACH (sd->under_items, l, it)
     {
        _round_item_del(sd, it);
     }
   sd->under_items = eina_list_free(sd->under_items);

   EINA_LIST_FOREACH (sd->over_items, l, it)
     {
        _round_item_del(sd, it);
     }
   sd->over_items = eina_list_free(sd->over_items);
}
