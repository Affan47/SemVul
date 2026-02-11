operator>>(Command aCommand_)
{
  switch (aCommand_)
  {
  case reset: _parseData->setPosition(0); break;
  case skip:  _parseData->processSkip();  break;
  default:                                break;
  }
  return *this;
}
