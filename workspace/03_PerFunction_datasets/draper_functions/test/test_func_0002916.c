SpawnConnection(int sd_reply,char *ipaddr)

{ struct cfd_connection *conn;

#ifdef HAVE_PTHREAD_H
 pthread_t tid;
#endif

conn = NewConn(sd_reply);

strncpy(conn->ipaddr,ipaddr,CF_MAX_IP_LEN-1);

CfOut(cf_verbose,"","New connection...(from %s:sd %d)\n",conn->ipaddr,sd_reply);

#if defined HAVE_LIBPTHREAD || defined BUILTIN_GCC_THREAD

CfOut(cf_verbose,"","Spawning new thread...\n");

pthread_attr_init(&PTHREADDEFAULTS);
pthread_attr_setdetachstate(&PTHREADDEFAULTS,PTHREAD_CREATE_DETACHED);

#ifdef HAVE_PTHREAD_ATTR_SETSTACKSIZE
pthread_attr_setstacksize(&PTHREADDEFAULTS,(size_t)1024*1024);
#endif

if (pthread_create(&tid,&PTHREADDEFAULTS,(void *)HandleConnection,(void *)conn) != 0)
   {
   CfOut(cf_error,"create","pthread_create failed");
   HandleConnection(conn);
   }

pthread_attr_destroy(&PTHREADDEFAULTS);

#else


CfOut(cf_verbose,"","Single threaded...\n");

HandleConnection(conn);

#endif
}
