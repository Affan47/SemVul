FuncIO_open(Obj self,Obj path,Obj flags,Obj mode)
{
  Int res;
  if (!IS_STRING(path) || !IS_STRING_REP(path) || !IS_INTOBJ(flags) ||
      !IS_INTOBJ(mode) ) {
      SyClearErrorNo();
      return Fail;
  } else {
      res = open((char *) CHARS_STRING(path),
                 INT_INTOBJ(flags),INT_INTOBJ(mode));
      if (res < 0) {
          SySetErrorNo();
          return Fail;
      } else
          return INTOBJ_INT(res);
  }
}
