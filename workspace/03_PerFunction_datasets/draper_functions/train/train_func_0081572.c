operator==(const SMSStoreEntry &e) const
{
  if (_message.isnull() || e._message.isnull())
    return _message.isnull() && e._message.isnull();
  else
    return _message->encode() == e._message->encode();
}
