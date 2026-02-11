set_spec (const char *name, const char *spec, bool user_p)
{
  struct spec_list *sl;
  const char *old_spec;
  int name_len = strlen (name);
  int i;


  if (!specs)
    {
      struct spec_list *next = (struct spec_list *) 0;
      for (i = ARRAY_SIZE (static_specs) - 1; i >= 0; i--)
	{
	  sl = &static_specs[i];
	  sl->next = next;
	  next = sl;
	}
      specs = sl;
    }


  for (sl = specs; sl; sl = sl->next)
    if (name_len == sl->name_len && !strcmp (sl->name, name))
      break;

  if (!sl)
    {

      sl = XNEW (struct spec_list);
      sl->name = xstrdup (name);
      sl->name_len = name_len;
      sl->ptr_spec = &sl->ptr;
      sl->alloc_p = 0;
      *(sl->ptr_spec) = "";
      sl->next = specs;
      specs = sl;
    }

  old_spec = *(sl->ptr_spec);
  *(sl->ptr_spec) = ((spec[0] == '+' && ISSPACE ((unsigned char)spec[1]))
		     ? concat (old_spec, spec + 1, NULL)
		     : xstrdup (spec));

#ifdef DEBUG_SPECS
  if (verbose_flag)
    fnotice (stderr, "Setting spec %s to '%s'\n\n", name, *(sl->ptr_spec));
#endif


  if (old_spec && sl->alloc_p)
    free (CONST_CAST(char *, old_spec));

  sl->user_p = user_p;
  sl->alloc_p = true;
}
