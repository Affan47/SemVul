checksum_format_specifier(const char* msg)
{
  ha_checksum chksum= 0;
  const uchar* p= (const uchar*) msg;
  const uchar* start= NULL;
  uint32 num_format_specifiers= 0;
  while (*p)
  {

    if (*p == '%')
    {
      start= p+1;
      num_format_specifiers++;
    }
    else if (start)
    {
      switch(*p)
      {
      case 'd':
      case 'u':
      case 'x':
      case 's':
        chksum= my_checksum(chksum, (uchar*) start, (uint) (p + 1 - start));
        start= 0;
        break;

      default:
        break;
      }
    }

    p++;
  }

  if (start)
  {


    fprintf(stderr, "Still inside formatspecifier after end of string"
                    " in'%s'\n", msg);
    DBUG_ASSERT(start==0);
  }


  chksum+= num_format_specifiers;

  return chksum;
}
