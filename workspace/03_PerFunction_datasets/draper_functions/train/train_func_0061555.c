_Cthread_self() {
#ifdef _CTHREAD
  void               *tsd = NULL;
#else
  struct Cid_element_t *current = &Cid;
  Cth_pid_t             pid;
#endif
  int                   n;


  if ( _Cthread_once_status && _Cthread_init() ) return(-1);


#ifdef _NOCTHREAD


  pid = getpid();
  n = -1;
  while (current->next != NULL) {
    current = current->next;
    if (current->pid == pid) {
      n = current->cid;
      break;
    }
  }


  return(n);

#else


#  if _CTHREAD_PROTO == _CTHREAD_PROTO_WIN32


#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_POSIX
  if ((n = pthread_once(&cid_once,&_Cthread_cid_once)) != 0) {
    errno = n;

    return(-1);
  }
#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_DCE
  if (pthread_once(&cid_once,&_Cthread_cid_once) != 0) {

    return(-1);
  }
#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_LINUX

  pthread_once(&cid_once,&_Cthread_cid_once);
#  else

  return(-1);
#  endif


#  if _CTHREAD_PROTO == _CTHREAD_PROTO_POSIX
  tsd = pthread_getspecific(cid_key);
#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_DCE
  if (pthread_getspecific(cid_key,&tsd)) {
    tsd = NULL;
  }
#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_LINUX
  tsd = pthread_getspecific(cid_key);
#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_WIN32
  tsd = TlsGetValue(cid_key);
#  else

  return(-1);
#  endif

  if (tsd == NULL) {


    if ((tsd = (void *) malloc(sizeof(int))) == NULL) {

      return(-1);
    }


#  if _CTHREAD_PROTO == _CTHREAD_PROTO_POSIX
    if ((n = pthread_setspecific(cid_key, tsd))) {
      errno = n;

      return(-1);
    }
#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_DCE
    if (pthread_setspecific(cid_key, tsd)) {

      return(-1);
    }
#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_LINUX
    if ((n = pthread_setspecific(cid_key, tsd))) {
      errno = n;

      return(-1);
    }
#  elif _CTHREAD_PROTO == _CTHREAD_PROTO_WIN32
    if ( !(n = TlsSetValue(cid_key, tsd)) ) {

      return(-1);
    }
#  else

    return(-1);
#  endif


    * (int *) tsd = -2;

    return(-2);

  } else {


    return((int) * (int *) tsd);

  }
#endif
}
