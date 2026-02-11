e_shelf_list_all(void)
{
   Eina_List *d = NULL, *s = NULL, *ret = NULL;

   if (shelves)
     s = eina_list_clone(shelves);
   if (dummies)
     d = eina_list_clone(dummies);
   if (s && d)
     ret = eina_list_merge(s, d);
   else
     ret = d ?: s;
   return ret;
}
