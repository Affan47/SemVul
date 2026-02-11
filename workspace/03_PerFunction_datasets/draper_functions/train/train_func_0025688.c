initDest(char *path, char **msg)
{
  static char message[LENGTH];
  char    vinfo[] = "vErSiO";
  datum   key, value;

  if (msg)
    *(*msg = message) = '\0';
  if (init_ok == 1)
    return 0;
  else if(init_ok == -1)
    return -1;
  if (!path || !*path) {
    if (msg)
      snprintf(message, LENGTH,
      "Dest V%s: Error: no destination database specified!", version);
    return init_ok = -1;
  }
  if ((db = OPEN(path, READ)) == 0) {
    if (msg)
      snprintf(message, LENGTH,
	       "Dest V%s: Error: open '%s': '%s'",
	       version, path, GET_ERR);
    return -1;
  }

  key.dptr = vinfo;
  key.dsize = 7;
  value = FETCH(db, key);
  if (value.dptr == 0) {
    if (msg)
      snprintf(message, LENGTH,
	       "Dest V%s: Error: File '%s': no Vinfo",
	       version, path);
    exitDest();
    return init_ok = -1;
  }
  if (msg)
    snprintf(message, LENGTH,
    "Dest V%s: File '%s' opened fine - %s", version, path, value.dptr);

  if (*dbv == 'G')
    free(value.dptr);
  init_ok = 1;
  return 0;
}
