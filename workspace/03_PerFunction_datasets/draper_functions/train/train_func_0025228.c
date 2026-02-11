opt_info_switch_p_1 (const char *arg, int *flags, int *optgroup_flags,
                     char **filename)
{
  const char *option_value;
  const char *ptr;

  option_value = arg;
  ptr = option_value;

  *filename = NULL;
  *flags = 0;
  *optgroup_flags = 0;

  if (!ptr)
    return 1;

  while (*ptr)
    {
      const struct dump_option_value_info *option_ptr;
      const char *end_ptr;
      const char *eq_ptr;
      unsigned length;

      while (*ptr == '-')
	ptr++;
      end_ptr = strchr (ptr, '-');
      eq_ptr = strchr (ptr, '=');

      if (eq_ptr && !end_ptr)
        end_ptr = eq_ptr;

      if (!end_ptr)
	end_ptr = ptr + strlen (ptr);
      length = end_ptr - ptr;

      for (option_ptr = optinfo_verbosity_options; option_ptr->name;
           option_ptr++)
	if (strlen (option_ptr->name) == length
	    && !memcmp (option_ptr->name, ptr, length))
          {
            *flags |= option_ptr->value;
	    goto found;
          }

      for (option_ptr = optgroup_options; option_ptr->name; option_ptr++)
	if (strlen (option_ptr->name) == length
	    && !memcmp (option_ptr->name, ptr, length))
          {
            *optgroup_flags |= option_ptr->value;
	    goto found;
          }

      if (*ptr == '=')
        {


          *filename = xstrdup (ptr + 1);
          break;
        }
      else
        {
          warning (0, "unknown option %q.*s in %<-fopt-info-%s%>",
                   length, ptr, arg);
          return 0;
        }
    found:;
      ptr = end_ptr;
    }

  return 1;
}
