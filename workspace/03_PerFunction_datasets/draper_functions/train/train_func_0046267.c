lookup_compiler (const char *name, size_t length, const char *language)
{
  struct compiler *cp;


  if (language != 0 && language[0] == '*')
    return 0;


  if (language != 0)
    {
      for (cp = compilers + n_compilers - 1; cp >= compilers; cp--)
	if (cp->suffix[0] == '@' && !strcmp (cp->suffix + 1, language))
	  return cp;

      error ("language %s not recognized", language);
      return 0;
    }


  for (cp = compilers + n_compilers - 1; cp >= compilers; cp--)
    {
      if (
	  (!strcmp (cp->suffix, "-") && !strcmp (name, "-"))
	  || (strlen (cp->suffix) < length

	      && !strcmp (cp->suffix,
			  name + length - strlen (cp->suffix))
	 ))
	break;
    }

#if defined (OS2) ||defined (HAVE_DOS_BASED_FILE_SYSTEM)

  if (cp < compilers)
    for (cp = compilers + n_compilers - 1; cp >= compilers; cp--)
      {
	if (
	    (!strcmp (cp->suffix, "-") && !strcmp (name, "-"))
	    || (strlen (cp->suffix) < length

		&& ((!strcmp (cp->suffix,
			     name + length - strlen (cp->suffix))
		     || !strpbrk (cp->suffix, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"))
		    && !strcasecmp (cp->suffix,
				    name + length - strlen (cp->suffix)))
	   ))
	  break;
      }
#endif

  if (cp >= compilers)
    {
      if (cp->spec[0] != '@')

	return cp;


      return lookup_compiler (NULL, 0, cp->spec + 1);
    }
  return 0;
}
