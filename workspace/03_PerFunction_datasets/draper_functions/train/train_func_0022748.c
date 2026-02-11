lCreateListHash(const char *listname, const lDescr *descr, bool hash)
{
   lList *lp;
   int i, n;

   DENTER(CULL_LAYER, "lCreateListHash");

   if (listname == NULL) {
      listname = "No list name specified";
   }

   if (!descr || mt_get_type(descr[0].mt) == lEndT) {
      LERROR(LEDESCRNULL);
      DRETURN(NULL);
   }

   if (!(lp = (lList *) malloc(sizeof(lList)))) {
      LERROR(LEMALLOC);
      DRETURN(NULL);
   }
   if (!(lp->listname = strdup(listname))) {
      FREE(lp);
      LERROR(LESTRDUP);
      DRETURN(NULL);
   }

   lp->nelem = 0;
   if ((n = lCountDescr(descr)) <= 0) {
      FREE(lp->listname);
      FREE(lp);
      LERROR(LECOUNTDESCR);
      DRETURN(NULL);
   }

   lp->first = NULL;
   lp->last = NULL;
   if (!(lp->descr = (lDescr *) malloc(sizeof(lDescr) * (n + 1)))) {
      FREE(lp->listname);
      FREE(lp);
      LERROR(LEMALLOC);
      DRETURN(NULL);
   }

   for (i = 0; i <= n; i++) {
      lp->descr[i].mt = descr[i].mt;
      lp->descr[i].nm = descr[i].nm;


      if(hash && mt_do_hashing(lp->descr[i].mt)) {
         lp->descr[i].ht = cull_hash_create(&descr[i], 0);
      } else {
         lp->descr[i].ht = NULL;
      }
      lp->descr[i].mt |= (descr[i].mt & CULL_IS_REDUCED);
   }

   lp->changed = false;

   DRETURN(lp);
}
