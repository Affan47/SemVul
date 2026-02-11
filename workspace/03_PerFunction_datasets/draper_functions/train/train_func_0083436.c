getGlobArgc(int argc, char *argv[], int globArgc)
{
  int streamInCnt;
  int streamOutCnt;
  char *opername;
  char *comma_position;
  const char *caller = processInqPrompt();

  opername = &argv[globArgc][1];
  comma_position = strchr(opername, ',');
  if ( comma_position ) *comma_position = 0;

  streamInCnt  = operatorStreamInCnt(opername);
  streamOutCnt = operatorStreamOutCnt(opername);

  if ( streamInCnt == -1 ) streamInCnt = 1;

  if ( streamOutCnt > 1 )
    Errorc("More than one output stream not allowed in CDO pipes (Operator %s)!", opername);

  globArgc++;

  if ( streamInCnt > 0 )
    globArgc = skipInputStreams(argc, argv, globArgc, streamInCnt);
  if ( comma_position ) *comma_position = ',';

  return (globArgc);
}
