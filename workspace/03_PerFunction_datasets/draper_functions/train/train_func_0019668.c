parse_historical (struct app_local_s *apploc,
                  const unsigned char * buffer, size_t buflen)
{

  if (buflen < 4)
    {
      log_error ("warning: historical bytes are too short\n");
      return;
    }
  if (*buffer)
    {
      log_error ("warning: bad category indicator in historical bytes\n");
      return;
    }


  buffer++;
  buflen--;


  apploc->status_indicator = buffer[buflen-3];
  buflen -= 3;


  while (buflen)
    {
      unsigned int tag = (*buffer & 0xf0) >> 4;
      unsigned int len = (*buffer & 0x0f);
      if (len+1 > buflen)
        {
          log_error ("warning: bad Compact-TLV in historical bytes\n");
          return;
        }
      buffer++;
      buflen--;
      if (tag == 7 && len == 3)
        {

          apploc->cardcap.cmd_chaining = !!(buffer[2] & 0x80);
          apploc->cardcap.ext_lc_le    = !!(buffer[2] & 0x40);
        }
      buffer += len;
      buflen -= len;
    }
}
