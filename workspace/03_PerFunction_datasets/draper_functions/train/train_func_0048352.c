_Cthread_cid_once()
{
  int n;


#ifndef _CTHREAD

  serrno = SEOPNOTSUP;
#else
#if _CTHREAD_PROTO == _CTHREAD_PROTO_POSIX

  if ((n = pthread_key_create(&cid_key,&_Cthread_cid_destructor))) {
    errno = n;
    serrno = SECTHREADERR;
  }
#elif _CTHREAD_PROTO == _CTHREAD_PROTO_DCE

  if (pthread_keycreate(&cid_key,&_Cthread_cid_destructor)) {
    serrno = SECTHREADERR;
  }
#elif _CTHREAD_PROTO == _CTHREAD_PROTO_LINUX

  if ((n = pthread_key_create(&cid_key,&_Cthread_cid_destructor))) {
    errno = n;
    serrno = SECTHREADERR;
  }
#elif _CTHREAD_PROTO == _CTHREAD_PROTO_WIN32
  if ( (n = TlsAlloc()) == 0xFFFFFFFF ) {
    serrno = SECTHREADERR;
  } else {
    cid_key = n;
  }
#else
  serrno = SEOPNOTSUP;
#endif
#endif
}
