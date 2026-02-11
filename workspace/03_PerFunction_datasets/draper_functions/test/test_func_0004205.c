_e_box_unpack_internal(E_Smart_Data *sd, E_Box_Item *bi)
{
   Eina_Inlist *l;

   l = EINA_INLIST_GET(sd->items);
   l = eina_inlist_remove(l, EINA_INLIST_GET(bi));
   sd->items = EINA_INLIST_CONTAINER_GET(l, E_Box_Item);
   sd->item_count--;
   _e_box_smart_disown(bi);
   sd->changed = 1;
   if (sd->frozen <= 0) _e_box_smart_reconfigure(sd);
}
