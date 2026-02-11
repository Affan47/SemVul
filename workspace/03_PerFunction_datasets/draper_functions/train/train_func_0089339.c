net_wait( DirectStream   *stream,
          unsigned int    length,
          struct timeval *tv )
{
     fd_set s;

     if (stream->cache_size >= length)
          return DR_OK;

     if (stream->fd == -1)
          return DR_EOF;

     FD_ZERO( &s );
     FD_SET( stream->fd, &s );

     switch (select( stream->fd+1, &s, NULL, NULL, tv )) {
          case 0:
               if (!tv && !stream->cache_size)
                    return DR_EOF;
               return DR_TIMEOUT;
          case -1:
               return errno2result( errno );
     }

     return DR_OK;
}
