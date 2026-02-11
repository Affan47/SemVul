loc_init()
   {
   struct tlentry *lptr, *lptr1;
   struct tcentry *cptr, *cptr1;
   int i;


   for (i = 0; i < lhsize; i++) {
      for (lptr = lhash[i]; lptr != NULL; lptr = lptr1) {
          lptr1 = lptr->l_blink;
          free((char *)lptr);
          }
       lhash[i] = NULL;
       }
   lfirst = NULL;
   llast = NULL;


   for (i = 0; i < lchsize; i++) {
      for (cptr = chash[i]; cptr != NULL; cptr = cptr1) {
          cptr1 = cptr->c_blink;
          free((char *)cptr);
          }
       chash[i] = NULL;
       }
   cfirst = NULL;
   clast = NULL;
   }
