TranslateFilename(string filename)
{
  string result;

  string::iterator p = filename.begin();
  while (p != filename.end())
  {
    unsigned char ch = *p;

    bool ok = true;
#ifdef WIN32
    if (ch < 32)
    {
      ok = false;
    }
    else
    {
      switch (ch)
      {
      case '"':
      case '*':
      case '/':
      case ':':
      case '<':
      case '>':
      case '?':
      case '\\':
      case '|':
        ok = false;
      }
    }
#else
    if (ch < 32)
    {
      ok = false;
    }
#endif


    if (ok)
    {
      result += ch;
    }
    else
    {

      result += ((ch >> 4) < 10) ? (ch >> 4) + '0' : (ch >> 4) + 'A'-10;
      result += ((ch & 0xf) < 10) ? (ch & 0xf) + '0' : (ch & 0xf) + 'A'-10;
    }

    ++p;
  }

  return result;
}
