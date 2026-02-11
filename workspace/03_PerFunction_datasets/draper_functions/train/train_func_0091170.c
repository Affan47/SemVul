send(Ref<SMSMessage> &ackPdu)
  throw(GsmException)
{
  return _mySMSStore->send(_index, ackPdu);
}
