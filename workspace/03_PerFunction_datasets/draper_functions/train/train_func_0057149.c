parseuint2(Logfile *lf, void *arg, char c) {
  unsigned int *x = (unsigned int *)arg;

  *block_end = '\0';
  if (!ISDIGIT(*pos)) {
    if (*pos == ' ')
      *x = 0;
    else
      return(FALSE);
  }
  else
    *x = *pos - '0';
  pos++;

  if (!ISDIGIT(*pos))
    return(TRUE);
  *x *= 10;
  *x += *pos - '0';
  pos++;
  return(TRUE);
}
