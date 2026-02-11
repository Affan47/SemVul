make_gcov_file_name (const char *input_name, const char *src_name)
{
  const char *cptr;
  char *name;

  if (flag_long_names && input_name && strcmp (src_name, input_name))
    {
      name = XNEWVEC (char, strlen (src_name) + strlen (input_name) + 10);
      name[0] = 0;

      cptr = flag_preserve_paths ? NULL : lbasename (input_name);
      strcat (name, cptr ? cptr : input_name);
      strcat (name, "##");
    }
  else
    {
      name = XNEWVEC (char, strlen (src_name) + 10);
      name[0] = 0;
    }


  cptr = flag_preserve_paths ? NULL : lbasename (src_name);
  strcat (name, cptr ? cptr : src_name);

  if (flag_preserve_paths)
    {


      char *pnew = name, *pold = name;


      while (*pold != '\0')
	{
	  if (*pold == '/' || *pold == '\\')
	    {
	      *pnew++ = '#';
	      pold++;
	    }
#if defined (HAVE_DOS_BASED_FILE_SYSTEM)
	  else if (*pold == ':')
	    {
	      *pnew++ = '~';
	      pold++;
	    }
#endif
	  else if ((*pold == '/' && strstr (pold, "/./") == pold)
		   || (*pold == '\\' && strstr (pold, "\\.\\") == pold))
	      pold += 3;
	  else if (*pold == '/' && strstr (pold, "/../") == pold)
	    {
	      strcpy (pnew, "/^/");
	      pnew += 3;
	      pold += 4;
	    }
	  else if (*pold == '\\' && strstr (pold, "\\..\\") == pold)
	    {
	      strcpy (pnew, "\\^\\");
	      pnew += 3;
	      pold += 4;
	    }
	  else
	    *pnew++ = *pold++;
	}

      *pnew = '\0';
    }

  strcat (name, ".gcov");
  return name;
}
