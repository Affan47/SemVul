kwsysSystem_Shell__CharNeedsQuotesOnUnix(char c)
{
  return ((c == '\'') || (c == '`') || (c == ';') || (c == '#') ||
          (c == '&') || (c == '$') || (c == '(') || (c == ')') ||
          (c == '~') || (c == '<') || (c == '>') || (c == '|') ||
          (c == '*') || (c == '^') || (c == '\\'));
}
