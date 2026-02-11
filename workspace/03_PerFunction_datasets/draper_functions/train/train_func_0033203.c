insertReadBuffer(char* data)
{
  int eof_insert = -1;

  if ( data == NULL || data[0] == '\0' ) return eof_insert;

  int data_len = strlen(data);

  eof_insert = readBufferPos + data_len;


  char* tmp = new char[readBufferLen + data_len];

  int i;

  for (i = 0; i < readBufferPos; i++) {
    tmp[i] = readBuffer[i];
  }


  for (i = 0; i < data_len; i++) {
    tmp[readBufferPos + i] = data[i];
  }


  for (i = readBufferPos; i < readBufferLen; i++) {
    tmp[data_len + i] = readBuffer[i];
  }


  delete[] readBuffer;
  readBuffer = tmp;

  readBufferLen += data_len;

  return eof_insert;
}
