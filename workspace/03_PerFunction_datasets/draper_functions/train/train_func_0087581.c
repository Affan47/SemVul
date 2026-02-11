getFloatOpt(int argc, char **argv, int i, float *value, int force)
{
  char *end;
  double v;

  if( ++i>=argc ) goto nothingFound;

  errno = 0;
  v = strtod(argv[i], &end);


  if( end==argv[i] ) goto nothingFound;


  while( isspace((int) *end) ) end+=1;
  if( *end ) goto nothingFound;


  checkFloatConversion(v, argv[i-1], argv[i]);

  *value = (float)v;

  return i;

nothingFound:
  if( !force ) return i-1;

  fprintf(stderr,
	  "%s: missing or malformed float value after option `%s'\n",
	  Program, argv[i-1]);
  exit(EXIT_FAILURE);

}
