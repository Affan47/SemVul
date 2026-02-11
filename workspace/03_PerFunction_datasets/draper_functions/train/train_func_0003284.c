builtin_handler (self, defs, arg)
     char *self;
     DEF_FILE *defs;
     char *arg;
{
  BUILTIN_DESC *new;
  char *name;


  if (building_builtin)
    {
      line_error (defs, "%s found before $END", self);
      return (-1);
    }

  output_cpp_line_info++;


  name = get_arg (self, defs, arg);


  if (!defs->builtins)
    defs->builtins = array_create (sizeof (BUILTIN_DESC *));

  new = (BUILTIN_DESC *)xmalloc (sizeof (BUILTIN_DESC));
  new->name = name;
  new->function = (char *)NULL;
  new->shortdoc = (char *)NULL;
  new->docname = (char *)NULL;
  new->longdoc = (ARRAY *)NULL;
  new->dependencies = (ARRAY *)NULL;
  new->flags = 0;

  if (is_special_builtin (name))
    new->flags |= BUILTIN_FLAG_SPECIAL;
  if (is_assignment_builtin (name))
    new->flags |= BUILTIN_FLAG_ASSIGNMENT;
  if (is_posix_builtin (name))
    new->flags |= BUILTIN_FLAG_POSIX_BUILTIN;

  array_add ((char *)new, defs->builtins);
  building_builtin = 1;

  return (0);
}
