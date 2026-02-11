httpEnqueueRequest ( connection, msg, read_function, callback,
  gen_callback )
sockfd connection;
char *msg;
#ifdef _NO_PROTO
httpError (*read_function)();
void (*callback)();
void (*gen_callback)();
#else
httpError (*read_function)(sockfd);
void (*callback)(char *);
void (*gen_callback)(char *,int);
#endif
{
  httpRequest *request;

  if ( num_requests >= MAX_REQUESTS_QUEUED - 1 ) {
    fprintf ( stderr, "Too many errors...\n" );
    return ( HTTP_TOO_MANY_REQUESTS );
  }


  request = (httpRequest *) malloc ( sizeof ( httpRequest ) );
  memset ( request, '\0', sizeof ( httpRequest ) );
  if ( msg ) {
    request->request = (char *) malloc ( strlen ( msg ) + 1 );
    strcpy ( request->request, msg );
    request->connection = connection;
  }
  else {

    request->request = NULL;
    request->sent = 1;
  }
  request->connection = connection;
  request->read_function = read_function;
  request->callback = callback;
  request->gen_callback = gen_callback;
  request->data_read = NULL;
  requests[num_requests++] = request;


  if ( num_requests == 1 ) {
    httpSendRequest ( requests[0] );
  }

  return ( HTTP_NO_ERROR );
}
