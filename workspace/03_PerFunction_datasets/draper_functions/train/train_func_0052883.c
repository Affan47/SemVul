VTThrd_isAlive()
{
  uint32_t *tid;


  tid = (uint32_t*)pthread_getspecific(pthreadKey);


  if (tid || masterThreadTerminated)
    return 1;
  else
    return 0;
}
