goOff(void)
{
  _timer=0;
  int myhandle=handle();
  if(Interval==_onExpire){open();}
  A data=_aEventData?getEventData():getExpiry();
  ACallback(_eventSymbol->n,data);
  dc(data);
  if(this!=AipcService::lookup(myhandle,TimrConnection::ServiceType))return;
  if(Destroy==_onExpire){delete this;return;}
  else if(Restart==_onExpire){open();}
}
