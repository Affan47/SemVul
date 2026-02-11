wiring_setup(PROGRAMMER * pgm)
{
  void *mycookie;


  stk500v2_setup(pgm);


  if ((mycookie = malloc(sizeof(struct wiringpdata))) == 0) {
    fprintf(stderr,
      "%s: wiring_setup(): Out of memory allocating private data\n",
      progname);
    exit(1);
  }
  memset(mycookie, 0, sizeof(struct wiringpdata));
  WIRINGPDATA(mycookie)->snoozetime = 0;


  STK500V2PDATA(pgm)->chained_pdata = mycookie;
}
