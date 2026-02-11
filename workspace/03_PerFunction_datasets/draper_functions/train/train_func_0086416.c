addNickJupes(const char *nicks)
{
  static char temp[BUFSIZE + 1];
  char* one;
  char* p;
  int   pos;

  if (nicks && *nicks)
  {
    ircd_strncpy(temp, nicks, BUFSIZE);
    temp[BUFSIZE] = '\0';
    p = NULL;
    for (one = ircd_strtok(&p, temp, ","); one; one = ircd_strtok(&p, NULL, ","))
    {
      if (!*one)
        continue;
      pos = strhash(one);
loop:
      pos &= JUPEHASHMASK;
      if (!jupeTable[pos][0])
      {
        if (jupesCount == JUPEMAX)
          return 1;
        jupesCount++;
        ircd_strncpy(jupeTable[pos], one, NICKLEN);
        jupeTable[pos][NICKLEN] = '\000';
        continue;
      }
      if (0 == ircd_strcmp(one, jupeTable[pos]))
        continue;
      ++pos;
      goto loop;
    }
  }
  return 0;
}
