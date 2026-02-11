passInMessageHandler(CoinMessageHandler * handler)
{
  if (defaultHandler_) {
    delete handler_;
    handler_ = NULL;
  }
  defaultHandler_=false;
  handler_=handler;
  if (modelPtr_)
    modelPtr_->passInMessageHandler(handler);
}
