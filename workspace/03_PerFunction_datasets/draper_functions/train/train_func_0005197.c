parseuint4strict(Logfile *lf, void *arg, char c) {
  unsigned int *x = (unsigned int *)arg;

  *block_end = '\0';
  if (!ISDIGIT(*pos))
    return(FALSE);
  *x = 1000 * (*pos - '0');
  pos++;

  if (!ISDIGIT(*pos))
    return(FALSE);
  *x += 100 * (*pos - '0');
  pos++;

  if (!ISDIGIT(*pos))
    return(FALSE);
  *x += 10 * (*pos - '0');
  pos++;

  if (!ISDIGIT(*pos))
    return(FALSE);
  *x += *pos - '0';
  pos++;
  return(TRUE);
}
