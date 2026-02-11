erl_eterm_free(void *p)
{
#ifdef PURIFY
  if (p) {
      memset(p, WIPE_CHAR, sizeof(ETERM));
  }
  free(p);
#else
  struct fix_block *b = p;

  if (b) {
      if (b->free) {
#ifdef DEBUG
	  fprintf(stderr,"erl_eterm_free: attempt to free already freed block %p\n",b);
#endif
	  return;
      }

#ifdef _REENTRANT
      ei_mutex_lock(erl_eterm_state->lock,0);
#endif
      b->free = 1;
      b->next = erl_eterm_state->freelist;
      erl_eterm_state->freelist = b;
      erl_eterm_state->freed++;
      erl_eterm_state->allocated--;
#ifdef _REENTRANT
      ei_mutex_unlock(erl_eterm_state->lock);
#endif
  }
#endif
}
