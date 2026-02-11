sh_erange (s, desc)
     char *s, *desc;
{
  if (s)
    builtin_error (_("%s: %s out of range"), s, desc ? desc : _("argument"));
  else
    builtin_error (_("%s out of range"), desc ? desc : _("argument"));
}
