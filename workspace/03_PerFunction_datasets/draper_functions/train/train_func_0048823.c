parsenewline(Logfile *lf, void *arg, char c) {

  *block_end = 'a';
  if (*pos != '\n' && *pos != ' ' && *pos != '\r' && *pos != '\t')
    return(FALSE);
  while (*pos == ' ' || *pos == '\t')
    pos++;
  if (pos == block_end && record_start != block_start) {
    shunt_data(lf);
    *block_end = 'a';
    while (*pos == ' ' || *pos == '\t')
      pos++;
  }

  if (*pos != '\n' && *pos != '\r')
    return(FALSE);
  termchar[(unsigned char)'\0'] = FALSE;
  while (termchar[(unsigned char)(*pos)])
    pos++;
  if (pos == block_end && record_start != block_start) {
    shunt_data(lf);
    *block_end = 'a';
    while (termchar[(unsigned char)(*pos)])
      pos++;
  }
  termchar[(unsigned char)'\0'] = TRUE;
  return(TRUE);
}
