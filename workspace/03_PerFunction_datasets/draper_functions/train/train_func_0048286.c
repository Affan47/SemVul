bookmark_cmp_dest
(  const void* bm1
,  const void* bm2
)
   {  const bookmark* mk1 = bm1
   ;  const bookmark* mk2 = bm2
   ;  int res
   ;  if ((res = strcmp(mk1->dest->str,mk2->dest->str)))
      return res
   ;  if ((res = (((int) mk2->info & BIT_LIST_DEST) - ((int) mk1->info & BIT_LIST_DEST))))
      return res
   ;  return strcmp(mk1->mark->str,mk2->mark->str)
;  }
