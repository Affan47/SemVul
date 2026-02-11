CanHandle(const char* NameString)
{
  if (0 == strcmp(NameString, "UTF-16"))
    {
    _endianExplicitlySet = false;
    return true;
    }
  else if (0 == strcmp(NameString, "UTF-16BE"))
    {
    SetBigEndian(true);
    return true;
    }
  else if (0 == strcmp(NameString, "UTF-16LE"))
    {
    SetBigEndian(false);
    return true;
    }
  else
    {
    return false;
    }
}
