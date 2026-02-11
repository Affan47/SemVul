LoadHandler( void )
{
  Char buf[256];
  LoadCStr(buf, 256);
  if (buf[0] == '\0')
    return (ObjFunc) 0;
  else
    return HandlerOfCookie(buf);
}
