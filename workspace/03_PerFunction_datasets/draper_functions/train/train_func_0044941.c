mm_log (char *string,long errflg)
{
  switch (errflg) {
  case BYE:
  case NIL:
    if (verbosep) fprintf (stderr,"[%s]\n",string);
    break;
  case PARSE:
  case WARN:
    fprintf (stderr,"warning: %s\n",string);
    break;
  case ERROR:
  default:
    fprintf (stderr,"%s\n",string);
    break;
  }
}
