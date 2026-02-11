maskname(int x)
{
  static char s[207];
  int i = 0;

  s[0] = 0;
  if (x & LOG_MSGS)
    i += my_strcpy(s, "msgs, ");
  if (x & LOG_PUBLIC)
    i += my_strcpy(s + i, "public, ");
  if (x & LOG_JOIN)
    i += my_strcpy(s + i, "joins, ");
  if (x & LOG_MODES)
    i += my_strcpy(s + i, "kicks/modes, ");
  if (x & LOG_CMDS)
    i += my_strcpy(s + i, "cmds, ");
  if (x & LOG_MISC)
    i += my_strcpy(s + i, "misc, ");
  if (x & LOG_BOTS)
    i += my_strcpy(s + i, "bots, ");
  if ((x & LOG_RAW) && raw_log)
    i += my_strcpy(s + i, "raw, ");
  if (x & LOG_FILES)
    i += my_strcpy(s + i, "files, ");
  if (x & LOG_SERV)
    i += my_strcpy(s + i, "server, ");
  if (x & LOG_DEBUG)
    i += my_strcpy(s + i, "debug, ");
  if (x & LOG_WALL)
    i += my_strcpy(s + i, "wallops, ");
  if ((x & LOG_SRVOUT) && raw_log)
    i += my_strcpy(s + i, "server output, ");
  if ((x & LOG_BOTNET) && raw_log)
    i += my_strcpy(s + i, "botnet traffic, ");
  if ((x & LOG_BOTSHARE) && raw_log)
    i += my_strcpy(s + i, "share traffic, ");
  if (x & LOG_LEV1)
    i += my_strcpy(s + i, "level 1, ");
  if (x & LOG_LEV2)
    i += my_strcpy(s + i, "level 2, ");
  if (x & LOG_LEV3)
    i += my_strcpy(s + i, "level 3, ");
  if (x & LOG_LEV4)
    i += my_strcpy(s + i, "level 4, ");
  if (x & LOG_LEV5)
    i += my_strcpy(s + i, "level 5, ");
  if (x & LOG_LEV6)
    i += my_strcpy(s + i, "level 6, ");
  if (x & LOG_LEV7)
    i += my_strcpy(s + i, "level 7, ");
  if (x & LOG_LEV8)
    i += my_strcpy(s + i, "level 8, ");
  if (i)
    s[i - 2] = 0;
  else
    strcpy(s, "none");
  return s;
}
