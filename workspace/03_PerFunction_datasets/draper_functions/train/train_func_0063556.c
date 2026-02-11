get_option_args(key, argc_ptr, argv_ptr)
     char *key;
     int *argc_ptr;
     char ***argv_ptr;
{
  int x, start, stop;
  int keylen;

  keylen = strlen(key);
  x = 0;
  while ((x < OptionsARGC) &&
	 ! ((strncasecmp(OptionsARGV[x], key, keylen) == 0) &&
	    (OptionsARGV[x][keylen] == KEYCHAR))) {
    x++;
  }

  if (x >= OptionsARGC) {
    *argc_ptr = -1;
    *argv_ptr = NULL;
    return FALSE;
  }

  start = x;

  while ((x < OptionsARGC) &&
	 ! ((strncasecmp(&(OptionsARGV[x][1]), key, keylen) == 0) &&
	    (OptionsARGV[x][0] == KEYCHAR))) {
    x++;
  }

  stop = x;

  *argc_ptr = stop - start - 1;


  *argv_ptr = &(OptionsARGV[start+1]);

  return TRUE;

}
