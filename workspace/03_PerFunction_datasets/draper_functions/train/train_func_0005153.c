nextlngstr(FILE *f, char *name, logical want) {

  while (TRUE) {
    if (getnextline(f, block_start, 0) == EOF) {
      if (want)
	error("language file %s too short", name);
      else
	return((char *)NULL);
    }
    if (strlen(block_start) >= 255)
      error("language file %s contains excessively long lines", name);
    if (block_start[0] != '#' || block_start[1] != '#') {
      if (want)
	return(block_start);
      else
	error("language file %s too long", name);
    }
  }
}
