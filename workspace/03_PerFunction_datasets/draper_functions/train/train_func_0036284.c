e_flowlayout_pack_before(Evas_Object *obj, Evas_Object *child, Evas_Object *before)
{
   E_Smart_Data *sd;
   int i = 0;
   Eina_List *l;
   Evas_Object *item;

   if (evas_object_smart_smart_get(obj) != _e_smart) SMARTERR(0);
   sd = evas_object_smart_data_get(obj);
   if (!sd) return 0;
   _e_flowlayout_smart_adopt(sd, child);
   sd->items = eina_list_prepend_relative(sd->items, child, before);
   EINA_LIST_FOREACH(sd->items, l, item)
     {
        if (item == child) break;
        i++;
     }
   sd->changed = 1;
   if (sd->frozen <= 0) _e_flowlayout_smart_reconfigure(sd);
   return i;
}
