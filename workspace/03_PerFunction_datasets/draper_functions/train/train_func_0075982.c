jump_protocol(const char *source) {
  int p;


  if ((p = strfield(source, "http:")))
    source += p;
  else if ((p = strfield(source, "ftp:")))
    source += p;
  else if ((p = strfield(source, "https:")))
    source += p;
  else if ((p = strfield(source, "file:")))
    source += p;

  if (strncmp(source, "//", 2) == 0)
    source += 2;
  return (char *) source;
}
