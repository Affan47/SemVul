passInMessageHandler(CoinMessageHandler * handler)
{
  if (defaultHandler_)
    delete handler_;
  defaultHandler_=false;
  handler_=handler;
}
