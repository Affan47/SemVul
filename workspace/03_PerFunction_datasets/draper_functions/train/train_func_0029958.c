cull_hash_remove(const lListElem *ep, const int pos)
{
   char host_key[CL_MAXHOSTLEN+1];
   cull_htable ht;
   void *key;

   if(ep == NULL || pos < 0) {
      return;
   }

   ht = ep->descr[pos].ht;


   if(ht == NULL) {
      return;
   }

   key = cull_hash_key(ep, pos, host_key);
   if(key != NULL) {
      if(mt_is_unique(ep->descr[pos].mt)) {
        sge_htable_delete(ht->ht, key);
      } else {
         union {
            non_unique_header *l;
            void *p;
         } head;
         union {
            non_unique_hash *l;
            void *p;
         } nuh;

         head.l = NULL;
         nuh.l = NULL;


         if(sge_htable_lookup(ht->ht, key, (const void **)&head.p) == True) {

            if (sge_htable_lookup(ht->nuht, &ep, (const void **)&nuh.p) == True) {
               if (head.l->first == nuh.p) {
                  head.l->first = nuh.l->next;
                  if (head.l->last == nuh.p) {
                     head.l->last = NULL;
                  } else {
                     head.l->first->prev = NULL;
                  }
               } else if (head.l->last == nuh.p) {
                  head.l->last = nuh.l->prev;
                  head.l->last->next = NULL;
               } else {
                  nuh.l->prev->next = nuh.l->next;
                  nuh.l->next->prev = nuh.l->prev;
               }

               sge_htable_delete(ht->nuht, &ep);
               free(nuh.p); nuh.p = NULL;
            } else {

            }

            if (head.l->first == NULL && head.l->last == NULL) {
               free(head.p); head.p = NULL;
               sge_htable_delete(ht->ht, key);
            }
         }
      }
   }
}
