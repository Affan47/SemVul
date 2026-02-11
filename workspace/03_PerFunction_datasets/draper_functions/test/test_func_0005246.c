VTThrd_getThreadId()
{
  uint32_t *tid;


  tid = (uint32_t*)pthread_getspecific(pthreadKey);


  if (tid == NULL && masterThreadTerminated)
    return 0;
  else
    vt_libassert(tid != NULL);

  return *tid;
}
