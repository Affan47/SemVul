clone()
{
  Ref<SMSStoreEntry> result = new SMSStoreEntry(_message->clone());
  result->_status = _status;
  result->_index = _index;
  return result;
}
