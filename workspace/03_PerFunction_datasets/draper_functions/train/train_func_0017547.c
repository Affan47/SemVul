_cache_mime_get(History_Types *ht, Evry_Item_File *file)
{
   History_Entry *he;
   History_Item *hi;
   Eina_List *l;

   if ((he = eina_hash_find(ht->types, file->path)))
     {
        EINA_LIST_FOREACH (he->items, l, hi)
          {
             if (!hi->data)
               continue;

             if (!file->mime)
               file->mime = hi->data;

             hi->transient = 0;
             EVRY_ITEM(file)->hi = hi;
             break;
          }
     }
}
