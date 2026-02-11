kwsysSystem_Shell__CharIsMakeVariableName(char c)
{
  return c && (c == '_' || isalpha(((int)c)));
}
