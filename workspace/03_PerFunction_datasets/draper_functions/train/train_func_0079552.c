prepareASCII (const UString& s)
{
  _originalPos = 0;


  CString truncated = s.cstring();
  _buffer = new char[truncated.size() + 1];
  memcpy(_buffer, truncated.c_str(), truncated.size());
  _buffer[truncated.size()] = '\0';
  _bufferSize = truncated.size();
}
