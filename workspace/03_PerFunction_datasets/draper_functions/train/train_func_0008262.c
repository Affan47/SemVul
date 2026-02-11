set_wstorage(JCR *jcr, USTORE *store)
{
   STORE *storage;

   if (!store->store) {
      return;
   }
   if (jcr->wstorage) {
      free_wstorage(jcr);
   }
   if (!jcr->wstorage) {
      jcr->wstorage = New(alist(10, not_owned_by_alist));
   }
   jcr->wstore = store->store;
   if (!jcr->wstore_source) {
      jcr->wstore_source = get_pool_memory(PM_MESSAGE);
   }
   pm_strcpy(jcr->wstore_source, store->store_source);
   Dmsg2(50, "wstore=%s where=%s\n", jcr->wstore->name(), jcr->wstore_source);
   foreach_alist(storage, jcr->wstorage) {
      if (store->store == storage) {
         return;
      }
   }

   jcr->wstorage->prepend(store->store);
}
