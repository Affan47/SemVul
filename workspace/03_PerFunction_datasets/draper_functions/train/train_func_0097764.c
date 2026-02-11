IDirectFBEventBuffer_WaitForEventWithTimeout( IDirectFBEventBuffer *thiz,
                                              unsigned int          seconds,
                                              unsigned int          milli_seconds )
{
     struct timeval  now;
     struct timespec timeout;
     DFBResult       ret    = DFB_OK;
     int             locked = 0;
     long int        nano_seconds = milli_seconds * 1000000;

     DIRECT_INTERFACE_GET_DATA(IDirectFBEventBuffer)

     D_DEBUG_AT( IDFBEvBuf, "%s( %p, %u, %u )\n", __FUNCTION__, thiz, seconds, milli_seconds );

     if (data->pipe)
          return DFB_UNSUPPORTED;

     if (pthread_mutex_trylock( &data->events_mutex ) == 0) {
          if (data->events) {
               pthread_mutex_unlock ( &data->events_mutex );
               return ret;
          }
          locked = 1;
     }

     gettimeofday( &now, NULL );

     timeout.tv_sec  = now.tv_sec + seconds;
     timeout.tv_nsec = (now.tv_usec * 1000) + nano_seconds;

     timeout.tv_sec  += timeout.tv_nsec / 1000000000;
     timeout.tv_nsec %= 1000000000;

     if (!locked)
          pthread_mutex_lock( &data->events_mutex );

     if (!data->events) {
          if (pthread_cond_timedwait( &data->wait_condition,
                                      &data->events_mutex,
                                      &timeout ) == ETIMEDOUT)
               ret = DFB_TIMEOUT;
          else if (!data->events)
               ret = DFB_INTERRUPTED;
     }

     pthread_mutex_unlock( &data->events_mutex );

     return ret;
}
