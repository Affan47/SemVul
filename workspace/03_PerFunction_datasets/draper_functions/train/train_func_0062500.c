ExecuteCommand(const string& command)
{
  string cmdstr = command;
  string args;
  int sppos = cmdstr.find(" ",0);
  if (sppos != string::npos) {
    args = cmdstr.substr(sppos+1);
    cmdstr = cmdstr.substr(0, sppos);
  }


  String_abbref_eq cmd( StrUpCase( cmdstr));

  if( cmd( "COMPILE"))
    {
      return CmdCompile( command);
    }
  if( cmd( "CONTINUE"))
    {
      return CC_CONTINUE;
    }
  if( cmd( "EDIT"))
    {
      cout << "Can't edit file without running GDLDE." << endl;
      return CC_OK;
    }
  if( cmd( "FULL_RESET_SESSION"))
    {
      return CmdFullReset();
    }
  if( cmd( "GO"))
    {
      cout << "GO not implemented yet." << endl;
      return CC_OK;
    }
  if( cmd( "OUT"))
    {
      cout << "OUT not implemented yet." << endl;
      return CC_OK;
    }
  if( cmd( "RUN"))
    {
      return CmdRun( command);
    }
  if( cmd( "RETURN"))
    {
      cout << "RETURN not implemented yet." << endl;
      return CC_OK;
    }
  if( cmd( "RESET_SESSION"))
    {
      return CmdReset();
    }
  if( cmd( "RNEW"))
    {
      cout << "RNEW not implemented yet." << endl;
      return CC_OK;
    }
  if( cmd( "SIZE"))
    {
      cout << "SIZE not implemented yet." << endl;
      return CC_OK;
    }
  if( cmd( "SKIP"))
    {
      DLong sCount;
      if( args == "")
      {
	  sCount = 1;
      }
      else
      {
	const char* cStart=args.c_str();
	char* cEnd;
	sCount = strtol(cStart,&cEnd,10);
	if( cEnd == cStart)
	{
	  cout << "Type conversion error: Unable to convert given STRING: '"+args+"' to LONG." << endl;
	  return CC_OK;
	}
      }
      stepCount = sCount;
      return CC_SKIP;
    }
  if( cmd( "STEP"))
    {
      DLong sCount;
      if( args == "")
      {
	  sCount = 1;
      }
      else
      {
	  const char* cStart=args.c_str();
	  char* cEnd;
	  sCount = strtol(cStart,&cEnd,10);
	  if( cEnd == cStart)
	  {
	    cout << "Type conversion error: Unable to convert given STRING: '"+args+"' to LONG." << endl;
	    return CC_OK;
	  }
	}
	stepCount = sCount;
	debugMode = DEBUG_STEP;
	return CC_STEP;
    }
  if( cmd( "STEPOVER"))
    {
      cout << "STEPOVER not implemented yet." << endl;
      return CC_OK;
    }
  if( cmd( "TRACE"))
    {
      cout << "TRACE not implemented yet." << endl;
      return CC_OK;
    }
  cout << SysVar::MsgPrefix() <<
    "Unknown command: "<< command << endl;
  return CC_OK;
}
