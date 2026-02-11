__pthread_cleanup_upto (__jmp_buf target, char *targetframe)
{
  struct pthread *self = THREAD_SELF;
  struct _pthread_cleanup_buffer *cbuf;


  uintptr_t adj = (uintptr_t) self->stackblock + self->stackblock_size;
  uintptr_t targetframe_adj = (uintptr_t) targetframe - adj;

  for (cbuf = THREAD_GETMEM (self, cleanup);
       cbuf != NULL && _JMPBUF_UNWINDS_ADJ (target, cbuf, adj);
       cbuf = cbuf->__prev)
    {
#if _STACK_GROWS_DOWN
      if ((uintptr_t) cbuf - adj <= targetframe_adj)
        {
          cbuf = NULL;
          break;
        }
#elif _STACK_GROWS_UP
      if ((uintptr_t) cbuf - adj >= targetframe_adj)
        {
          cbuf = NULL;
          break;
        }
#else
# error "Define either _STACK_GROWS_DOWN or _STACK_GROWS_UP"
#endif


      cbuf->__routine (cbuf->__arg);
    }

  THREAD_SETMEM (self, cleanup, cbuf);
}
