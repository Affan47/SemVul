mcxBufExtend
(  mcxBuf*     buf
,  dim         n_request
,  mcxOnFail   ON_FAIL
)
   {  dim   oldsize     =     buf->n
   ;  char **usrpptr    =     (char **) buf->mempptr
   ;  char* dummy

   ;  if (buf->bFinalized)
      mcxErr("mcxBufExtend PBD", "extending finalized buffer")

   ;  if (buf->n_alloc < buf->n + n_request)
      {  dim n_new
         =  MAX
            (  (dim) (buf->n_alloc * buf->factor + 8)
            ,  (dim) (buf->n + n_request)
            )

      ;  dummy = mcxRealloc(*usrpptr, n_new * buf->size, ON_FAIL)

      ;  if (n_new && !dummy)
         {  mcxMemDenied(stderr,"mcxBufExtend","char",buf->n*buf->size)
         ;  return NULL
      ;  }

         buf->n_alloc = n_new
      ;  *usrpptr = dummy
   ;  }

      buf->n += n_request
   ;  return *usrpptr + (oldsize * buf->size)
;  }
