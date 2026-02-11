is_varname (string)
     char *string;
{
  char *p;

  if(string == NIL)
    return(FALSE);

  if(string[0] != '+')
    return(FALSE);
  else
    if (string[1] == '\0')
      return(TRUE);

  p = &string[1];


  return (vardef_position (p) > -1);
}
