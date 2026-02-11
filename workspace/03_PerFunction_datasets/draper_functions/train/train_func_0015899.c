Info_Validate (const char *s)
{
  if (strchr(s, '"'))
    return false;
  if (strchr(s, ';'))
    return false;
  return true;
}
