_pan_item_remove(Evas_Object *obj, Item *it)
{
   Smart_Data *sd = evas_object_smart_data_get(obj);

   sd->items = eina_list_remove(sd->items, it);

   _item_hide(it);

   evry_item_free(it->item);

   sd->place = EINA_TRUE;
   _e_smart_reconfigure(obj);

   E_FREE(it);
}
