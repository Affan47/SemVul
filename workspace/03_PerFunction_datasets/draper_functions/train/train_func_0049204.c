install (void)
{


  const char *outfile = getenv ("PCPROFILE_OUTPUT");

  if (outfile != NULL && *outfile != '\0')
    {
      fd = open (outfile, O_RDWR | O_CREAT, 0666);

      if (fd != -1)
	{
	  uint32_t word;

	  active = 1;


	  word = 0xdeb00000 | sizeof (void *);
	  if (TEMP_FAILURE_RETRY (write (fd, &word, 4)) != 4)
	    {

	      close (fd);
	      fd = -1;
	      active = 0;
	    }
	}
    }
}
