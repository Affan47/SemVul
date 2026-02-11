cmos_init ()
{


  char *fls[] = {
#ifdef __ia64__
    "/dev/efirtc",
    "/dev/misc/efirtc",
#endif
    "/dev/rtc",
    "/dev/rtc0",
    "/dev/misc/rtc",
    NULL
  };
  char **p=fls;

  if (using_dev_rtc < 0)
    {
      while ((cmos_device=*p++))
	{
	  cmos_fd = open (cmos_device, O_RDONLY);
	  if (cmos_fd >= 0)
	    {
	      if (verbose)
		fprintf (stdout, "opened %s for reading\n", cmos_device);
	      using_dev_rtc = 1;
	      return;
	    }
	  if (verbose)
	    {
	      int saveerr=errno;
	      fprintf (stdout, "adjtimex: cannot open %s for reading\n",
		       cmos_device);
	      errno = saveerr;
	      perror("adjtimex");
	    }
	}

      using_dev_rtc = 0;
    }
  else if (using_dev_rtc > 0)
    return;


  cmos_init_directisa();
}
