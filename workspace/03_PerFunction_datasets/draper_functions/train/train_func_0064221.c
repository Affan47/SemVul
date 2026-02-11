Get(String& bufferout) const
{
  String tmp;
  bufferout.trunc();

  searchKey.Get(tmp);
  bufferout << "Input: searchKey = " << tmp << ", action = " <<  action << "; Output: collectRes " << (collectRes ? "set" : "not set");
  found.Get(tmp);
  bufferout << ", found = " << tmp << ", status = " << status;
  prefixKey.Get(tmp);
  bufferout << "; Internal State: prefixKey = " << tmp << ", cursor_get_flags = " << cursor_get_flags;

  return OK;
}
