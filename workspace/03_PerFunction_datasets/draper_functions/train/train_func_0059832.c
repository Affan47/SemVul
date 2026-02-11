bindRuleError (code, pos)
     int code;
     char *pos;
{
  int saveCode = curRule->status;

  curRule->status = code;
  bindRuleErrorPtr = pos;

  if (code && atBindDisplayErrors) reportError ();

  atBindError = TRUE;
  strcpy (atBindErrorMsg, "rule scan error(s)");

  if (saveCode)
    curRule->status = saveCode;
}
