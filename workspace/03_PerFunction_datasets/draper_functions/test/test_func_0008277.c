tag_table_to_type_alist (void *closure, SCM key, SCM val, SCM acc)
{
  if (scm_is_integer (key))
    {
      int c_tag = scm_to_int (key);

      char const * name = scm_i_tag_name (c_tag);
      if (name != NULL)
	{
	  key = scm_from_locale_string (name);
	}
      else
	{
	  char s[100];
	  sprintf (s, "tag %d", c_tag);
	  key = scm_from_locale_string (s);
	}
    }

  return scm_cons (scm_cons (key, val), acc);
}
