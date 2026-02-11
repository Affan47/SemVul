argc_argv (char *instr, argv_t ** argv, char *commentstr)
{
  char quote = '\0';
  int arg_count = 0;
  enum state_t
  {
    WHITESPACE, WORDSPACE, TOKENSTART
  } state = WHITESPACE;
  argv_t *argv_array = NULL;
  int argc_slots = 0;
  size_t len, pos;

  len = strlen (instr);
  pos = 0;
  char quoted = 0;

  while (pos < len)
    {


      if ((state == WHITESPACE) && (strchr (commentstr, *instr)))
	{
	  while ((*instr != '\n') && (*instr != '\0'))
	    {
	      instr++;
	      pos++;
	    }
	}

      switch (*instr)
	{


	case '"':
	case '\'':

	  if (state == WHITESPACE)
	    {
	      quote = *instr;
	      state = TOKENSTART;
	      quoted = -1;
	      if (*(instr + 1) == quote)
		{
		  *instr = '\0';
		}
	      else
		{
		  instr++;
		  pos++;
		}
	    }
	  else
	    {

	      if ( (*instr == quote) && quoted )
		{
		  quote = '\0';
		  *instr = '\0';
		  state = WHITESPACE;
		}
	    }
	  break;


	case '\\':
	  if ((quote) && (*(instr + 1) == quote))
	    {
	      memmove (instr, instr + 1, strlen (instr));
	      len--;
	    }

	  else
	    {
	      if (state == WHITESPACE)
		{
		  state = TOKENSTART;
		}
	    }
	  break;


	case ' ':
	case '\t':
	case '\r':
	case '\n':
	  if ((state == WORDSPACE) && (quote == '\0'))
	    {
	      state = WHITESPACE;
	      *instr = '\0';
	    }
	  break;

	case '\0':
	  break;

	default:
	  if (state == WHITESPACE)
	    {
	      state = TOKENSTART;
	    }

	}

      if (state == TOKENSTART)
	{
	  arg_count++;
	  if (arg_count > argc_slots)
	    {
	      argc_slots += ALLOC_CHUNK;
	      argv_array =
		(argv_t *) xrealloc (argv_array,
				     sizeof (argv_t) * (argc_slots +
							ALLOC_CHUNK));
	    }

	  if (argv_array == NULL)
	    {
	      return (-1);
	    }
	  argv_array[arg_count - 1].string = instr;
	  argv_array[arg_count - 1].quoted = quoted;
	  state = WORDSPACE;
	  quoted = 0;
	}

      instr++;
      pos++;
    }

  if ( arg_count == 0 ) return (0);

  argv_array[arg_count].string = NULL;
  *argv = argv_array;
  return (arg_count);
}
