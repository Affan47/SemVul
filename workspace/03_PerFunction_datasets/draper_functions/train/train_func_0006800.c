netsnmp_os_prematch(const char *ospmname,
                    const char *ospmrelprefix)
{
#if HAVE_SYS_UTSNAME_H
static int printOSonce = 1;
  struct utsname utsbuf;
  if ( 0 != uname(&utsbuf))
    return -1;

  if (printOSonce) {
    printOSonce = 0;

  DEBUGMSGT(("daemonize","sysname '%s',\nrelease '%s',\nversion '%s',\nmachine '%s'\n",
      utsbuf.sysname, utsbuf.release, utsbuf.version, utsbuf.machine));
  }
  if (0 != strcasecmp(utsbuf.sysname, ospmname)) return -1;


  return strncasecmp(utsbuf.release, ospmrelprefix, strlen(ospmrelprefix));

#else

  return -1;

#endif
}
