putenv (str)
#ifndef HAVE_STD_PUTENV
     const char *str;
#else
     char *str;
#endif
{
  SHELL_VAR *var;
  char *name, *value;
  int offset;

  if (str == 0 || *str == '\0')
    {
      errno = EINVAL;
      return -1;
    }

  offset = assignment (str, 0);
  if (str[offset] != '=')
    {
      errno = EINVAL;
      return -1;
    }
  name = savestring (str);
  name[offset] = 0;

  value = name + offset + 1;


  var = bind_variable (name, value, 0);
  if (var == 0)
    {
      errno = EINVAL;
      return -1;
    }

  VUNSETATTR (var, att_invisible);
  VSETATTR (var, att_exported);

  return 0;
}
