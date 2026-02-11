mcxBDBhash
(  const void *key
,  u32        len
)
   {  const char* k  =  key
   ;  u32   hash     =  0

   ;  while (len--)
      {  hash = *k++ + (hash << 6) + (hash << 16) - hash
   ;  }
      return hash
;  }
