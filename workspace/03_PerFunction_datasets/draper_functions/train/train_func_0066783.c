muscle_percent_define_get_raw (char const *variable, char const *field)
{
  uniqstr name = muscle_name (variable, field);
  char const *res = muscle_find_const (name);
  if (!res)
    complain (NULL, fatal, _("%s: undefined %%define variable %s"),
              "muscle_percent_define_get_raw", quote (variable));
  return res;
}
