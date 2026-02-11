get_lang_args (struct file_link const *flink)
{
  struct lang_args *args = lang_args_list;
  char *file_name = alloca (PATH_MAX);

  while (args)
    {
      if (strchr (args->la_pattern, SLASH_CHAR))
	{
	  absolute_file_name (file_name, flink);
	  if (fnmatch (args->la_pattern, file_name, MAYBE_FNM_CASEFOLD | FNM_FILE_NAME) == 0)
	    return (args->la_language ? args : 0);
	}
      else
	{
	  if (fnmatch (args->la_pattern, flink->fl_name, MAYBE_FNM_CASEFOLD) == 0)
	    return (args->la_language ? args : 0);
	}
      args = args->la_next;
    }
  return ((lang_args_default && lang_args_default->la_language)
	  ? lang_args_default : 0);
}
