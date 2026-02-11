Cthread_Mutex_Unlock(file, line, addr)
     char *file;
     int line;
     void *addr;
{
#ifdef _CTHREAD
  struct Cmtx_element_t *current = &Cmtx;
  int                  n;
#endif

#ifdef CTHREAD_DEBUG
  if (file != NULL) {
    if (Cthread_debug != 0)
      log(LOG_INFO,
          "[Cthread    [%2d]] In Cthread_unlock_mtx(0x%lx) called at/behind %s:%d\n",
          _Cthread_self(),(unsigned long) addr,
          file, line);
  }
#endif


  if ( _Cthread_once_status && _Cthread_init() ) return(-1);


  if (addr == NULL) {
    serrno = EINVAL;
    return(-1);
  }

#ifdef _NOCTHREAD

  return(0);
#else


  if (_Cthread_obtain_mtx(file,line,&(Cthread.mtx),-1))
    return(-1);

  n = 1;
  while (current->next != NULL) {
    current = current->next;
    if (current->addr == addr) {
      n = 0;
      break;
    }
  }

  _Cthread_release_mtx(file,line,&(Cthread.mtx));

  if (n) {

    serrno = EINVAL;
    return(-1);
  } else {
    return(_Cthread_release_mtx(file,line,&(current->mtx)));
  }
#endif
}
