eina_inlist_remove(Eina_Inlist *list, Eina_Inlist *item)
{
   Eina_Inlist *return_l;


   EINA_SAFETY_ON_NULL_RETURN_VAL(list, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(item, list);
   if (EINA_UNLIKELY((item != list) && (!item->prev) && (!item->next)))
     {
        eina_error_set(EINA_ERROR_SAFETY_FAILED);
        EINA_LOG_ERR("safety check failed: item %p does not appear to be part of an inlist!", item);
        return list;
     }

   if (item->next)
      item->next->prev = item->prev;

   if (item->prev)
     {
        item->prev->next = item->next;
        return_l = list;
     }
   else
     {
        return_l = item->next;
        if (return_l)
           return_l->last = list->last;
     }

   if (item == list->last)
      list->last = item->prev;

   item->next = NULL;
   item->prev = NULL;
   return return_l;
}
