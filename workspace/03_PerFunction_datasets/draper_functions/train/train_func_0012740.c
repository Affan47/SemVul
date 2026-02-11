read_server (FILE *outfp)
{
  char *recvline;
  int notdone = 1;

  while (notdone && ((recvline = read_line (serv_read, NULL)) != NULL))
    {
      if (debug)
	{
	  fprintf (stderr, "%s: received `%s'\n", program_name, recvline);
	}

      if (memcmp (recvline, ".\r\n\0", 4) == 0)
	{
	  notdone = 0;
	}
      else
	{
	  int i;
	  if (recvline[1])
	    {
	      size_t linelen = strlen (recvline) - 2;
	      if (recvline[linelen] == '\r')
		{


		  recvline[linelen] = '\n';
		  recvline[linelen + 1] = '\0';
		}
	    }

	  i = 0;
	  if (recvline[0] == '.')
	    {
	      i = 1;
	    }
	  fprintf (outfp, "%s", recvline + i);
	}
      free (recvline);
    }
}
