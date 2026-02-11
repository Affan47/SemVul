EcaSdii(void *argument)
{
  ECA_REQUEST_1 request;
  char lnamebuffer[1024];
  double threshold = 1;

  cdoInitialize(argument);
  cdoOperatorAdd("eca_sdii", 0, 31, NULL);

  if ( operatorArgc() == 1 ) threshold = atof(operatorArgv()[0]);
  if ( operatorArgc() > 1 ) cdoAbort("Too many arguments!");

  sprintf(lnamebuffer, SDII_LONGNAME, threshold);

  request.var1.name     = SDII_NAME;
  request.var1.longname = lnamebuffer;
  request.var1.units    = SDII_UNITS;
  request.var1.f1       = farselgec;
  request.var1.f1arg    = threshold;
  request.var1.f2       = farsum;
  request.var1.f3       = NULL;
  request.var1.mulc     = 0.0;
  request.var1.addc     = 0.0;
  request.var1.epilog   = MEAN;
  request.var2.h2       = NULL;
  request.var2.h3       = NULL;

  eca1(&request);
  cdoFinish();

  return (0);
}
