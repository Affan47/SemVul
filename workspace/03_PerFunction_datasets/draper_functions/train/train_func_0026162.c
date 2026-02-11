Cthread_Detach(file, line, cid)
     char *file;
     int line;
     int cid;
{
  struct Cid_element_t *current = &Cid;
  int                 n;
  int detached;

#ifdef CTHREAD_DEBUG
  if (file != NULL) {
    if (Cthread_debug != 0)
      log(LOG_INFO,
          "[Cthread    [%2d]] In Cthread_detach(%d) called at/behind %s:%d\n",
          _Cthread_self(),cid,file,line);
  }
#endif


  if ( _Cthread_once_status && _Cthread_init() ) return(-1);


  if (_Cthread_obtain_mtx(file,line,&(Cthread.mtx),-1))
    return(-1);

  n = 1;
  while (current->next != NULL) {
    current = current->next;
    if (current->cid == cid) {
      n = 0;
      detached = current->detached;
      current->detached = 1;
      break;
    }
  }
  _Cthread_release_mtx(file,line,&(Cthread.mtx));

  if (n) {
    serrno = EINVAL;
    return(-1);
  }

#ifdef _NOCTHREAD

  return(0);
#else


  if (detached) {

    return(0);
  }

#if _CTHREAD_PROTO == _CTHREAD_PROTO_POSIX
  if ((n = pthread_detach(current->pid))) {
    errno = n;
    serrno = SECTHREADERR;
    return(-1);
  }
#elif _CTHREAD_PROTO == _CTHREAD_PROTO_DCE

  {
    int status;
    Cth_pid_t thispid;

    memcpy(&thispid,&(current->pid),sizeof(Cth_pid_t));
    if (pthread_detach(&thispid)) {
      serrno = SECTHREADERR;
      return(-1);
    }
  }
#elif _CTHREAD_PROTO == _CTHREAD_PROTO_LINUX
  if ((n = pthread_detach(current->pid))) {
    errno = n;
    serrno = SECTHREADERR;
    return(-1);
  }
#elif _CTHREAD_PROTO ==  _CTHREAD_PROTO_WIN32

#else
  serrno = SEOPNOTSUP;
  return(-1);
#endif
  return(0);
#endif
}
