blocking_receive(unsigned char *buf, int length)
{
  int bytes_or_error;
  int byte_count = 0;

  system_tick_t _millis = callback_millis();

  while (length > byte_count)
  {
    bytes_or_error = callback_receive(buf + byte_count, length - byte_count);
    if (0 > bytes_or_error)
    {

      return bytes_or_error;
    }
    else if (0 < bytes_or_error)
    {
      byte_count += bytes_or_error;
    }
    else
    {
      if (20000 < (callback_millis() - _millis))
      {

        return -1;
      }
    }
  }
  return byte_count;
}
