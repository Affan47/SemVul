read_pattern_file(char *name, patstr **patptr, patstr **patlastptr, int popts)
{
int linenumber = 0;
FILE *f;
char *filename;
char buffer[PATBUFSIZE];

if (strcmp(name, "-") == 0)
  {
  f = stdin;
  filename = stdin_name;
  }
else
  {
  f = fopen(name, "r");
  if (f == NULL)
    {
    fprintf(stderr, "pcregrep: Failed to open %s: %s\n", name, strerror(errno));
    return FALSE;
    }
  filename = name;
  }

while (fgets(buffer, PATBUFSIZE, f) != NULL)
  {
  char *s = buffer + (int)strlen(buffer);
  while (s > buffer && isspace((unsigned char)(s[-1]))) s--;
  *s = 0;
  linenumber++;
  if (buffer[0] == 0) continue;


  *patlastptr = add_pattern(buffer, *patlastptr);
  if (*patlastptr == NULL)
    {
    if (f != stdin) fclose(f);
    return FALSE;
    }
  if (*patptr == NULL) *patptr = *patlastptr;


  for(;;)
    {
    if (!compile_pattern(*patlastptr, pcre_options, popts, TRUE, filename,
        linenumber))
      {
      if (f != stdin) fclose(f);
      return FALSE;
      }
    (*patlastptr)->string = NULL;
    if ((*patlastptr)->next == NULL) break;
    *patlastptr = (*patlastptr)->next;
    }
  }

if (f != stdin) fclose(f);
return TRUE;
}
