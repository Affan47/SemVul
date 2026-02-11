flames_fileutils_dot_replace (const char * name)

{
  static char str[PATHSET_MAX];
  char  *cpp;

  int  len;


  FLAMES_TRACE(__func__)


    if (name == NULL) return NULL;


  if (*name != '.')
    {
      len = (int) strlen(name);
      if (len > (PATHSET_MAX-1))
	{
	  cpl_msg_error (cpl_func, "Buffer overflow in filename '%s' - fatal error", name);
	  abort();
	}

      (void) strcpy (str, name);
      return (str);
    }


  cpp = getenv ("PWD");
  if (cpp != NULL)
    {
      len = (int) strlen(cpp);
      if (len > (PATHSET_MAX-1))
	{
	  cpl_msg_error (cpl_func, "Buffer overflow in filename '%s' - fatal error", name);
	  abort();
	}

      (void) strcpy (str,cpp);
    }
  else
    {
      cpl_msg_error (cpl_func, "Env. variable PWD not set - fatal errorn");
      abort();
    }


  if (*(name + 1) == '.')
    {
      if ((len+2) > (PATHSET_MAX-1))
	{
	  cpl_msg_error (cpl_func, "Buffer overflow in filename '%s' - fatal error", name);
	  abort();
	}
      (void) strcat (str, "/.");
      len += 2;
    }

  len = (int) strlen(str) + (int) strlen(name);
  if (len > PATHSET_MAX)
    {
      cpl_msg_error (cpl_func, "Buffer overflow in filename '%s'", name);
      cpl_msg_error (cpl_func, "Fatal error replacing current working "
		     "directory symbol due to buffer overflow");
      abort();
    }
  (void) strcat(str, name + 1);

  return (str);
}
