_item_find(Evas_Object *obj,
           const void *data)
{
   Eina_List *l;
   Elm_Index_Item *it;

   ELM_INDEX_DATA_GET(obj, sd);

   EINA_LIST_FOREACH (sd->items, l, it)
     if (it->base.data == data) return it;

   return NULL;
}
