is_line (const ACE_TCHAR *line)
{
  while (*line && ACE_OS::ace_isspace (*line))
    ++line;

  return *line != ACE_TEXT ('\0');
}
