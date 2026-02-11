claCheck(
     ClaElem *cla
)
#else
static Boolean claCheck(cla)
     ClaElem *cla;
#endif
{
  Boolean ok = FALSE;

  if ((cla->classes&(Aword)CLA_OBJ) != 0)
    ok = ok || isObj(params[cla->code-1].code);
  if ((cla->classes&(Aword)CLA_CNT) != 0)
    ok = ok || isCnt(params[cla->code-1].code);
  if ((cla->classes&(Aword)CLA_ACT) != 0)
    ok = ok || isAct(params[cla->code-1].code);
  if ((cla->classes&(Aword)CLA_NUM) != 0)
    ok = ok || isNum(params[cla->code-1].code);
  if ((cla->classes&(Aword)CLA_STR) != 0)
    ok = ok || isStr(params[cla->code-1].code);
  if ((cla->classes&(Aword)CLA_COBJ) != 0)
    ok = ok || (isCnt(params[cla->code-1].code) && isObj(params[cla->code-1].code));
  if ((cla->classes&(Aword)CLA_CACT) != 0)
    ok = ok || (isCnt(params[cla->code-1].code) && isAct(params[cla->code-1].code));
  return ok;
}
