getString(istream& file) {
  int   bufsz     = 512;
  char* buf       = new char[bufsz];
  char* p         = buf;
  char  c;


  do {
    if (!file.get(c)) {
      delete [] buf;
      return 0;
    }
    if (c == '#') {
      do {
	if (!file.get(c)) {
	  delete [] buf;
	  return 0;
	}
      } while (c != '\n');
    }
  } while (isspace(c));

  *p++ = c;


  while (1) {
    if (!file.get(c)) {
      delete [] buf;
      return 0;
    }
    if (isspace(c)) {
      *p = '\0';
      return buf;
    }
    *p++ = c;

    if (p == (buf + bufsz)) {

      char *obuf = buf;
      buf = new char[bufsz+bufsz];
      memcpy(buf, obuf, bufsz);
      delete [] obuf;
      p = buf + bufsz;
      bufsz += bufsz;
    }
  }
}
