FuncIO_make_sockaddr_in(Obj self,Obj ip,Obj port)
{
  struct sockaddr_in sa;
  Obj res;
  if (!IS_INTOBJ(port) || !IS_STRING(ip) || !IS_STRING_REP(ip) ||
      GET_LEN_STRING(ip) != 4) {
      SyClearErrorNo();
      return Fail;
  } else {
      memset(&sa,0,sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = htons(INT_INTOBJ(port));
      memcpy(&(sa.sin_addr.s_addr),CHARS_STRING(ip),4);
      res = NEW_STRING(sizeof(sa));
      memcpy(CHARS_STRING(res),&sa,sizeof(sa));
      return res;
  }
}
