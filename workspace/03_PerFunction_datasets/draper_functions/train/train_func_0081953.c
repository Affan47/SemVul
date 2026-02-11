esl_stack_CCreate(void)
{
  ESL_STACK *cs = NULL;
  int status;

  ESL_ALLOC(cs, sizeof(ESL_STACK));
  cs->nalloc   = ESL_STACK_INITALLOC;
  cs->idata    = NULL;
  cs->pdata    = NULL;
  ESL_ALLOC(cs->cdata, sizeof(char) * cs->nalloc);
  cs->n        = 0;

#ifdef HAVE_PTHREAD
  cs->do_mutex = FALSE;
  cs->do_cond  = FALSE;
  cs->mutex    = NULL;
  cs->cond     = NULL;
#endif
  return cs;

 ERROR:
  esl_stack_Destroy(cs);
  return NULL;
}
