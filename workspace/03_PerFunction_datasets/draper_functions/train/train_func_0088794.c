crashreport_hexdump(unsigned long pid,void *data,size_t size,size_t offset)
{
  const unsigned char *block = data;
  char                *p;
  char                 line[80];
  char                 ascii[LINESIZE + 1];
  int                  skip;
  int                  j;

  syslog(LOG_ALERT,"CRASH(%lu/%03d): STACK DUMP",pid,m_cnt++);

  while(size > 0)
  {
    p = line;
    p += sprintf(p,"%08lX: ",(unsigned long)offset);

    for (skip = offset % LINESIZE , j = 0 ; skip ; j++ , skip--)
    {
      p += sprintf(p,"   ");
      ascii[j] = ' ';
    }

    do
    {
      p += sprintf(p,"%02X ",*block);
      if (isprint(*block))
        ascii[j] = *block;
      else
        ascii[j] = '.';

      block++;
      offset++;
      j++;
      size--;
    } while ((j < LINESIZE) && (size > 0));

    ascii[j] = '\0';

    if (j < LINESIZE)
    {
      int i;

      for (i = j ; i < LINESIZE ; i++)
        p += sprintf(p,"   ");
    }
    syslog(LOG_ALERT,"CRASH(%lu/%03d):        %s",pid,m_cnt++,line);
  }
}
