add_specific_symbols (const char *filename, htab_t htab)
{
  off_t  size;
  FILE * f;
  char * line;
  char * buffer;
  unsigned int line_count;

  size = get_file_size (filename);
  if (size == 0)
    {
      status = 1;
      return;
    }

  buffer = (char *) xmalloc (size + 2);
  f = fopen (filename, FOPEN_RT);
  if (f == NULL)
    fatal (_("cannot open '%s': %s"), filename, strerror (errno));

  if (fread (buffer, 1, size, f) == 0 || ferror (f))
    fatal (_("%s: fread failed"), filename);

  fclose (f);
  buffer [size] = '\n';
  buffer [size + 1] = '\0';

  line_count = 1;

  for (line = buffer; * line != '\0'; line ++)
    {
      char * eol;
      char * name;
      char * name_end;
      int finished = FALSE;

      for (eol = line;; eol ++)
	{
	  switch (* eol)
	    {
	    case '\n':
	      * eol = '\0';

	      if (eol[1] == '\r')
		++ eol;
	      finished = TRUE;
	      break;

	    case '\r':
	      * eol = '\0';

	      if (eol[1] == '\n')
		++ eol;
	      finished = TRUE;
	      break;

	    case 0:
	      finished = TRUE;
	      break;

	    case '#':


	      * eol = '\0';
	      break;

	    default:
	      break;
	    }

	  if (finished)
	    break;
	}


      for (name = line; IS_WHITESPACE (* name); name ++)
	;
      for (name_end = name;
	   (! IS_WHITESPACE (* name_end))
	   && (! IS_LINE_TERMINATOR (* name_end));
	   name_end ++)
	;

      if (! IS_LINE_TERMINATOR (* name_end))
	{
	  char * extra;

	  for (extra = name_end + 1; IS_WHITESPACE (* extra); extra ++)
	    ;

	  if (! IS_LINE_TERMINATOR (* extra))
	    non_fatal (_("%s:%d: Ignoring rubbish found on this line"),
		       filename, line_count);
	}

      * name_end = '\0';

      if (name_end > name)
	add_specific_symbol (name, htab);


      line = eol;
      line_count ++;
    }
}
