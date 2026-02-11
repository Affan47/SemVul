main(int argc, char *argv[])
{
    OFConsoleApplication app(OFFIS_CONSOLE_APPLICATION, "Test libi2d's BMP support", rcsid);
    OFCommandLine cmd;
    cmd.setOptionColumns(LONGCOL, SHORTCOL);
    cmd.setParamColumn(LONGCOL + SHORTCOL + 4);

    cmd.addGroup("general options:", LONGCOL, SHORTCOL + 2);
      cmd.addOption("--help",    "-h",     "print this help text and exit", OFCommandLine::AF_Exclusive);
      cmd.addOption("--version",           "print version information and exit", OFCommandLine::AF_Exclusive);
      OFLog::addOptions(cmd);


    prepareCmdLineArgs(argc, argv, OFFIS_CONSOLE_APPLICATION);
    if (app.parseCommandLine(cmd, argc, argv, OFCommandLine::PF_ExpandWildcards))
    {

      if (cmd.hasExclusiveOption())
      {
        if (cmd.findOption("--version"))
        {
          app.printHeader(OFTrue );
          return 0;
        }
      }
    }


    OFLog::configureFromCommandLine(cmd, app);


    OFLOG_DEBUG(i2dbmpLogger, rcsid << OFendl);

    testImages();


    unlink(temporaryFile);

    if (status)
    {
        LOG_WARN("!!! Some tests failed!");
    } else {
        COUT << "*** All tests successful!" << OFendl;
    }
    return status;
}
