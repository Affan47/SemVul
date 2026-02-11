imdsock_accept(void * v) {
  int rc;
  imdsocket *new_s = NULL, *s = (imdsocket *) v;
#if defined(ARCH_AIX5) || defined(ARCH_AIX5_64) || defined(ARCH_AIX6_64)
  unsigned int len;
#define _SOCKLEN_TYPE unsigned int
#elif defined(SOCKLEN_T)
  SOCKLEN_T len;
#define _SOCKLEN_TYPE SOCKLEN_T
#elif defined(_POSIX_SOURCE) || (defined(__APPLE__) && defined(__MACH__)) || defined(__linux)
  socklen_t len;
#define _SOCKLEN_TYPE socklen_t
#else
#define _SOCKLEN_TYPE int
  int len;
#endif

  len = sizeof(s->addr);
  rc = accept(s->sd, (struct sockaddr *) &s->addr, ( _SOCKLEN_TYPE * ) &len);
  if (rc >= 0) {
    new_s = (imdsocket *) malloc(sizeof(imdsocket));
    if (new_s != NULL) {
      *new_s = *s;
      new_s->sd = rc;
    }
  }
  return (void *)new_s;
}
