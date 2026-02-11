updateSleep (TimeoutId tid, EndpTCB func, int timeToSleep,
                       void *clientData)
{
  if (tid == 0)
    return prepareSleep (func, timeToSleep, clientData) ;
  else
    {

      removeTimeout (tid) ;
      return prepareSleep (func, timeToSleep, clientData) ;
    }
}
