openTempFile(GooString **name, FILE **f, char *mode) {
#if defined(_WIN32)

  char *tempDir;
  GooString *s, *s2;
  char buf[32];
  FILE *f2;
  int t, i;


  if ((tempDir = getenv("TEMP"))) {
    s = new GooString(tempDir);
    s->append('\\');
  } else {
    s = new GooString();
  }
  s->append("x");
  t = (int)time(NULL);
  for (i = 0; i < 1000; ++i) {
    sprintf(buf, "%d", t + i);
    s2 = s->copy()->append(buf);
    if (!(f2 = fopen(s2->getCString(), "r"))) {
      if (!(f2 = fopen(s2->getCString(), mode))) {
	delete s2;
	delete s;
        return gFalse;
      }
      *name = s2;
      *f = f2;
      delete s;
      return gTrue;
    }
    fclose(f2);
    delete s2;
  }
  delete s;
  return gFalse;
#elif defined(VMS) || defined(__EMX__) || defined(ACORN) || defined(MACOS)

  char *s;


  if (!(s = tmpnam(NULL))) {
    return gFalse;
  }
  *name = new GooString(s);
  if (!(*f = fopen((*name)->getCString(), mode))) {
    delete (*name);
    return gFalse;
  }
  return gTrue;
#else

  char *s;
  int fd;

#if HAVE_MKSTEMP
  if ((s = getenv("TMPDIR"))) {
    *name = new GooString(s);
  } else {
    *name = new GooString("/tmp");
  }
  (*name)->append("/XXXXXX");
  fd = mkstemp((*name)->getCString());
#else
  if (!(s = tmpnam(NULL))) {
    return gFalse;
  }
  *name = new GooString(s);
  fd = open((*name)->getCString(), O_WRONLY | O_CREAT | O_EXCL, 0600);
#endif
  if (fd < 0 || !(*f = fdopen(fd, mode))) {
    delete *name;
    return gFalse;
  }
  return gTrue;
#endif
}
