eina_inlist_append_relative(Eina_Inlist *list,
                            Eina_Inlist *new_l,
                            Eina_Inlist *relative)
{
   EINA_SAFETY_ON_NULL_RETURN_VAL(new_l, list);

   if (relative)
     {
        if (relative->next)
          {
             new_l->next = relative->next;
             relative->next->prev = new_l;
          }
        else
           new_l->next = NULL;

        relative->next = new_l;
        new_l->prev = relative;
        if (!new_l->next)
           list->last = new_l;

        return list;
     }

   return eina_inlist_append(list, new_l);
}
