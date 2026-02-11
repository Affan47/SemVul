equal_class (char s, const char *&p, bool case_sensitive)
  {
    ++p;
    bool negate = false;
    if (*p == '!')
      {
        negate = true;
        ++p;
      }

    for (bool first = true; *p && (first || *p != ']'); ++p)
      {
        if (!first && *p == '-' && p[1] != ']')
          {
            if (!p[1] || p[1] <= p[-1])
              {
                continue;
              }


            for (char range = p[-1] + 1; range <= p[1]; ++range)
              {
                if (equal_char (s, range, case_sensitive))
                  {
                    while (*++p != ']') {}
                    return !negate;
                  }
              }
            ++p;
          }
        else if (equal_char (s, *p, case_sensitive))
          {
            while (*++p != ']') {}
            return !negate;
          }
        first = false;
      }
    return negate;
  }
