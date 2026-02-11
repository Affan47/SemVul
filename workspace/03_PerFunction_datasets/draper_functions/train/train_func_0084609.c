FuncIO_sendto(Obj self,Obj fd,Obj st,Obj offset,Obj count,Obj flags,
                  Obj to)
{
  Int bytes;
  socklen_t fromlen;

  if (!IS_INTOBJ(fd) || !IS_STRING(st) || !IS_STRING_REP(st) ||
      !IS_INTOBJ(offset) || !IS_INTOBJ(count) || !IS_INTOBJ(flags) ||
      !IS_STRING(to) || !IS_STRING_REP(to)) {
      SyClearErrorNo();
      return Fail;
  }
  if (GET_LEN_STRING(st) < INT_INTOBJ(offset)+INT_INTOBJ(count)) {
      SyClearErrorNo();
      return Fail;
  }
  fromlen = GET_LEN_STRING(to);
  bytes = (Int) sendto(INT_INTOBJ(fd),
                       (char *) CHARS_STRING(st)+INT_INTOBJ(offset),
                       INT_INTOBJ(count),INT_INTOBJ(flags),
                       (struct sockaddr *)CHARS_STRING(to),fromlen);
  if (bytes < 0) {
      SySetErrorNo();
      return Fail;
  } else
      return INTOBJ_INT(bytes);
}
