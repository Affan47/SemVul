main(int  argc,
     char *argv[])
{
  int		i;
  ipp_t		*event;
  ipp_state_t	state;


  setbuf(stderr, NULL);

  fprintf(stderr, "DEBUG: argc=%d\n", argc);
  for (i = 0; i < argc; i ++)
    fprintf(stderr, "DEBUG: argv[%d]=\"%s\"\n", i, argv[i]);
  fprintf(stderr, "DEBUG: TMPDIR=\"%s\"\n", getenv("TMPDIR"));

  for (;;)
  {
    event = ippNew();
    while ((state = ippReadFile(0, event)) != IPP_DATA)
    {
      if (state <= IPP_IDLE)
        break;
    }

    if (state == IPP_ERROR)
      fputs("DEBUG: ippReadFile() returned IPP_ERROR!\n", stderr);

    if (state <= IPP_IDLE)
    {
      ippDelete(event);
      return (0);
    }

    print_attributes(event, 4);
    ippDelete(event);


    if (!strcmp(argv[1], "testnotify://nowait"))
      return (0);
  }
}
