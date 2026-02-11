numeric(char *str)
{
  int n = strlen(str);
  for (int i = 0; i < n; i++) {
    if (isdigit(str[i])) continue;
    if (str[i] == '-' || str[i] == '+' || str[i] == '.') continue;
    if (str[i] == 'e' || str[i] == 'E') continue;
    error->all(FLERR,
               "Expected floating point parameter in variable definition");
  }

  return atof(str);
}
