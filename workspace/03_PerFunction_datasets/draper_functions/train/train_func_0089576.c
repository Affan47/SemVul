open_giffile(const char *name)
{
  struct StoredFile *sf;
  FILE *f;

  if (name == 0 || strcmp(name, "-") == 0) {
#ifndef OUTPUT_GIF_TO_TERMINAL
    extern int isatty(int);
    if (isatty(fileno(stdin))) {
      error(0, "<stdin>: is a terminal");
      return NULL;
    }
#endif
#if defined(_MSDOS) || defined(_WIN32)
    _setmode(_fileno(stdin), _O_BINARY);
#elif defined(__DJGPP__)
    setmode(fileno(stdin), O_BINARY);
#elif defined(__EMX__)
    _fsetmode(stdin, "b");
#endif
    return stdin;
  }

  if (nextfile)
    for (sf = stored_files; sf; sf = sf->next)
      if (strcmp(name, sf->name) == 0)
	return sf->f;

  f = fopen(name, "rb");

  if (f && nextfile) {
    sf = (struct StoredFile *) malloc(sizeof(struct StoredFile) + strlen(name));
    sf->f = f;
    sf->next = stored_files;
    stored_files = sf;
    strcpy(sf->name, name);
  } else if (!f)
    error(0, "%s: %s", name, strerror(errno));

  return f;
}
