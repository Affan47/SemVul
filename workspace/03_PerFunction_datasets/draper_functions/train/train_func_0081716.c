_index_box_clear(Evas_Object *obj,
                 Evas_Object *box __UNUSED__,
                 int level)
{
   Eina_List *l;
   Elm_Index_Item *it;

   ELM_INDEX_DATA_GET(obj, sd);

   if (!sd->level_active[level]) return;

   EINA_LIST_FOREACH (sd->items, l, it)
     {
        if (!VIEW(it)) continue;
        if (it->level != level) continue;

        evas_object_del(VIEW(it));
        VIEW(it) = NULL;
     }

   sd->level_active[level] = 0;
}
