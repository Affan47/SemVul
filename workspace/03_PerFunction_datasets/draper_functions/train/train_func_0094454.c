llookup(id)
char *id;
   {
   register struct lentry *ptr;

   ptr = proc_lst->lhash[LHasher(id)];
   while (ptr != NULL && ptr->name != id)
      ptr = ptr->blink;
   return ptr;
   }
