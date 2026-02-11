EcaCsu(void *argument)
{
  double argT = 25.0;
  ECA_REQUEST_1 request;

  cdoInitialize(argument);
  cdoOperatorAdd("eca_csu", 0, 31, NULL);

  if ( operatorArgc() > 0 ) argT = atof(operatorArgv()[0]);

  request.var1.name     = CSU_NAME;
  request.var1.longname = CSU_LONGNAME;
  request.var1.units    = NULL;
  request.var1.f1       = farselgtc;
  request.var1.f1arg    = TO_KELVIN(argT);
  request.var1.f2       = farnum2;
  request.var1.f3       = farmax;
  request.var1.mulc     = 0.0;
  request.var1.addc     = 0.0;
  request.var1.epilog   = NONE;
  request.var2.h2       = NULL;
  request.var2.h3       = NULL;

  eca1(&request);
  cdoFinish();

  return (0);
}
