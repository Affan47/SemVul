escape_backslashes(const char *instr, char **outstr)
{
  int out_idx=0;

  if (*outstr != NULL) free(*outstr);
  *outstr = malloc(2*strlen(instr));

  while (*instr != '\0') {
    if (*instr=='\\') {
      *(*outstr+out_idx) = '\\';
      out_idx++;
    }
    *(*outstr+out_idx) = *instr;
    out_idx++;
    instr++;
  }
  *(*outstr+out_idx) = '\0';
}
