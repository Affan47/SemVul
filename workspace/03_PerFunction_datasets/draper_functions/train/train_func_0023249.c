EcaCwdi(void *argument)
{
  char *longname;
  int argN = 6;
  double argT = 5.0;
  ECA_REQUEST_2 request;

  cdoInitialize(argument);
  cdoOperatorAdd("eca_cwdi", 0, 31, NULL);

  if ( operatorArgc() > 0 ) argN = atoi(operatorArgv()[0]);
  if ( operatorArgc() > 1 ) argT = atof(operatorArgv()[1]);

  longname = (char *) malloc(strlen(CWDI_LONGNAME) + 80);
  sprintf(longname, CWDI_LONGNAME, argN, argT);

  request.var1.name     = CWDI_NAME;
  request.var1.longname = longname;
  request.var1.units    = CWDI_UNITS;
  request.var1.f1       = NULL;
  request.var1.f2       = farcsub;
  request.var1.f2arg    = argT;
  request.var1.f3       = farsellt;
  request.var1.f4       = farnum2;
  request.var1.f5       = farnum3;
  request.var1.f5arg    = argN;
  request.var1.epilog   = NONE;
  request.var2.name     = CWDI_NAME2;
  request.var2.longname = CWDI_LONGNAME2;
  request.var2.units    = CWDI_UNITS2;
  request.var2.h1       = farseleqc;
  request.var2.h1arg    = argN;
  request.var2.h2       = farnum;

  eca2(&request);

  free(longname);
  cdoFinish();

  return (0);
}
