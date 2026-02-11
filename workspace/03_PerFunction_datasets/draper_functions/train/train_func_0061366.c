add_to_message(unsigned char* buff, const char* format, ...)
{
  va_list ap;
  int n;

  assert(buff != NULL);
  assert(format != NULL);

  if (!newmessage) {
    n = strlen((char*) &buff[5]);
  }
  else {
    n = 0;
  }
  newmessage = 0;
  va_start(ap, format);

  vsprintf((char*) &buff[5+n], format, ap);
  n = strlen((char*) &buff[5]);
  sprintf((char*) &buff[5+n], "\n");

  va_end(ap);
}
