NetTCPPrintf( pal_socket_t sock, char *out, sint32_t pl, char *Format, ... )
{
  va_list argp;
  sint32_t Length;
  char Data[1024];

  va_start(argp, Format);
  pal_vsnprintf(Data, sizeof Data, Format, argp);
  va_end(argp);

  Length = pal_strlen(Data);

  if( NetTCPWrite(sock, Data, pal_strlen(Data)) != Length )
  {
    return 0;
  }

  return NetTCPRead(sock, out, pl);
}
