mcx_hash_double
(  mcxHash* h
)
   {  mcx_bucket* ole_bucket  =  h->buckets
   ;  mcx_bucket* ole_buckets =  h->buckets
   ;  dim d                   =  h->n_buckets
   ;  dim n_fail              =  0

   ;  if (h->options & MCX_HASH_DOUBLING)
      {  mcxErr("mcx_hash_double PANIC", "double trouble")
      ;  return STATUS_FAIL
   ;  }

      h->options |= MCX_HASH_DOUBLING

   ;  if
      (! (  h->buckets
         =  mcxNAlloc
            (  2 * h->n_buckets
            ,  sizeof(mcx_bucket)
            ,  mcx_bucket_init
            ,  RETURN_ON_FAIL
      )  )  )
      {  h->options ^= MCX_HASH_DOUBLING
      ;  h->buckets = ole_buckets
      ;  return STATUS_FAIL
   ;  }

      h->n_buckets  *=  2
   ;  h->n_entries   =  0

   ;  while(d-- > 0)
      {  hash_link* this   =  ole_bucket->base

      ;  while(this)
         {  hash_link* next = this->next, *clone
         ;  void* val   =  this->kv.val
         ;  void* key   =  this->kv.key

         ;  mcxGrimLet(h->src_link, this)
#if TINGEA_HASH_CACHE
         ;  clone = mcx_bucket_search(h, key, MCX_DATUM_INSERT, &this->hv)
#else
         ;  clone = mcx_bucket_search(h, key, MCX_DATUM_INSERT, NULL)
#endif

         ;  if (clone)
            clone->kv.val = val
         ;  else
            n_fail++

         ;  this = next
      ;  }
         ole_bucket++
   ;  }

      if (n_fail)
      mcxErr
      (  "mcx_hash_double PANIC"
      ,  "<%ld> reinsertion failures in hash with <%ld> entries"
      ,  (long) n_fail
      ,  (long) h->n_entries
      )

   ;  mcxFree(ole_buckets)
   ;  h->options ^= MCX_HASH_DOUBLING
   ;  return STATUS_OK
;  }
