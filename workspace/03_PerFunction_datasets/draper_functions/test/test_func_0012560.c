passInMessageHandler(CoinMessageHandler * handler)
{
  OsiSolverInterface::passInMessageHandler(handler);
  if (modelPtr_)
    modelPtr_->passInMessageHandler(handler);
}
