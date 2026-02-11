scm_i_allocate_string_pointers (SCM list)
{
  char **result;
  int len = scm_ilength (list);
  int i;

  if (len < 0)
    scm_wrong_type_arg_msg (NULL, 0, list, "proper list");

  scm_dynwind_begin (0);

  result = (char **) scm_malloc ((len + 1) * sizeof (char *));
  result[len] = NULL;
  scm_dynwind_unwind_handler (free, result, 0);


  for (i = 0; i < len && scm_is_pair (list); i++)
    {
      result[i] = scm_to_locale_string (SCM_CAR (list));
      list = SCM_CDR (list);
    }

  scm_dynwind_end ();
  return result;
}
