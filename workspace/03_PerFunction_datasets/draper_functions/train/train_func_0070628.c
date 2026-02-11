parse_configline(char *line,int *nopt)
{
  static char *retv[MAX_LINE_OPTIONS];
  int opt;
  for (opt=0;opt<MAX_LINE_OPTIONS;opt++)
  {

    while ((*line==' ')||(*line=='\t'))
      line++;

    if ((*line=='\0')||(*line=='#'))
      break;

    retv[opt]=line;

    while ((*line!=' ')&&(*line!='\t')&&(*line!='\0'))
      line++;

    if (*line!='\0')
      *line++='\0';
  }
  *nopt=opt;
  return retv;
}
