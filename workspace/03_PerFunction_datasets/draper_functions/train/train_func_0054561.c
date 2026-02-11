flames_fileutils_tilde_replace (const char * name)

{
  static char str[PATHSET_MAX];
  char *marker, *cpp;

  int  len;


    if (name == NULL) return NULL;


  if (*name != '~')
    {
      len = (int) strlen(name);
      if (len > (PATHSET_MAX-1))
	{
	  cpl_msg_error (cpl_func, "Buffer overflow in filename '%s' - fatal error", name);
	  abort();
	}
      (void) strcpy (str, name);
    }

  else
    {
      cpp = getenv ("HOME");
      if (cpp == NULL)
	{
	  cpl_msg_error (cpl_func, "Env. variable HOME not set, could not replace `~'");
	  abort();
	}

      (void) strcpy (str,cpp);
      len = (int) strlen(str) + (int) strlen(name);
      if (len > PATHSET_MAX)
	{
	  cpl_msg_error (cpl_func, "Buffer overflow in filename '%s' - fatal error", name);
	  abort();
	}

      (void) strcat (str, name + 1);
    }


  marker = strstr (str, "//");
  while (marker != NULL)
    {
      memmove (marker, marker + 1, strlen (marker));
      marker = strstr (str, "//");
    }


  marker = str - 1 + (int) strlen(str);
  if ((*marker) == '/') *marker = '\0';

#ifdef HAVE_WORDEXP
  return (flames_fileutils_env_replace (str));
#else

  return (str);
#endif

}
