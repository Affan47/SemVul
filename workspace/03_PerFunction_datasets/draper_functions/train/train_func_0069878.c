Detect_If_Aux_Name(int func)
{
  char *str = atom_tbl[func].name;
  char *p, *q;


  if (*str != '$' || (p = strstr(str, AUX_STR)) == NULL)
    return NULL;

  q = p + sizeof(AUX_STR) - 1;
  if (!isdigit(*q))
    return NULL;

  while (isdigit(*++q))
    ;

  if (*q != '\0')
    return NULL;

  while (isdigit(*--p) && p > str)
    ;

  if (*p != '/')
    return NULL;

  return p;
}
