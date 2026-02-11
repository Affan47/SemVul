FuncPRINT_CPROMPT( Obj self, Obj prompt )
{
  if (IS_STRING_REP(prompt)) {


    strlcpy(promptBuf, CSTR_STRING(prompt), sizeof(promptBuf));
    Prompt = promptBuf;
  }
  Pr("%s%c", (Int)Prompt, (Int)'\03' );
  return (Obj) 0;
}
