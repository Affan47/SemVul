ReadLstLine(char *buf, int nBytes)
{
  if (buf && nBytes && cpu)
    return ((Processor *)cpu)->files.ReadLine(((Processor *)cpu)->files.list_id(),lst_line,buf,nBytes);

  return buf;
}
