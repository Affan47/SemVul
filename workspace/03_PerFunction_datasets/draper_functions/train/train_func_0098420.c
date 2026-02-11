main(int argc, char *argv[])
{
#ifdef _MSC_VER

  _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


  CommandLine *commandline = new CommandLine;

  Result result = eInvalidCommandLineArguments;

  if (!commandline->Parse(argc, argv))
  {
    banner();
    CommandLine::usage();
  }
  else
  {
    if (commandline->GetNoiseLevel() > CommandLine::nlSilent)
      banner();


    switch (commandline->GetOperation())
    {
    case CommandLine::opCreate:
      {


        Par2Creator *creator = new Par2Creator;
        result = creator->Process(*commandline);
        delete creator;
      }
      break;
    case CommandLine::opVerify:
      {

        switch (commandline->GetVersion())
        {
        case CommandLine::verPar1:
          {
            Par1Repairer *repairer = new Par1Repairer;
            result = repairer->Process(*commandline, false);
            delete repairer;
          }
          break;
        case CommandLine::verPar2:
          {
            Par2Repairer *repairer = new Par2Repairer;
            result = repairer->Process(*commandline, false);
            delete repairer;
          }
          break;
        case CommandLine::opNone:
          break;
        }
      }
      break;
    case CommandLine::opRepair:
      {

        switch (commandline->GetVersion())
        {
        case CommandLine::verPar1:
          {
            Par1Repairer *repairer = new Par1Repairer;
            result = repairer->Process(*commandline, true);
            delete repairer;
          }
          break;
        case CommandLine::verPar2:
          {
            Par2Repairer *repairer = new Par2Repairer;
            result = repairer->Process(*commandline, true);
            delete repairer;
          }
          break;
        case CommandLine::opNone:
          break;
        }
      }
      break;
    case CommandLine::opNone:
      break;
    }
  }

  delete commandline;

  return result;
}
