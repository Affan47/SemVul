ExecuteLinkScript(std::vector<std::string>& args)
{


  bool verbose = false;
  if(args.size() >= 4)
    {
    if(args[3].find("--verbose=") == 0)
      {
      if(!cmSystemTools::IsOff(args[3].substr(10).c_str()))
        {
        verbose = true;
        }
      }
    }


  cmsysProcess* cp = cmsysProcess_New();
  if(!cp)
    {
    std::cerr << "Error allocating process instance in link script."
              << std::endl;
    return 1;
    }


  cmsysProcess_SetPipeShared(cp, cmsysProcess_Pipe_STDOUT, 1);
  cmsysProcess_SetPipeShared(cp, cmsysProcess_Pipe_STDERR, 1);


  cmsysProcess_SetOption(cp, cmsysProcess_Option_Verbatim, 1);


  std::ifstream fin(args[2].c_str());
  if(!fin)
    {
    std::cerr << "Error opening link script \""
              << args[2] << "\"" << std::endl;
    return 1;
    }


  std::string command;
  int result = 0;
  while(result == 0 && cmSystemTools::GetLineFromStream(fin, command))
    {

    const char* cmd[2] = {command.c_str(), 0};
    cmsysProcess_SetCommand(cp, cmd);


    if(verbose)
      {
      std::cout << command << std::endl;
      }


    cmsysProcess_Execute(cp);
    cmsysProcess_WaitForExit(cp, 0);


    switch(cmsysProcess_GetState(cp))
      {
      case cmsysProcess_State_Exited:
        {
        int value = cmsysProcess_GetExitValue(cp);
        if(value != 0)
          {
          result = value;
          }
        }
        break;
      case cmsysProcess_State_Exception:
        std::cerr << "Error running link command: "
                  << cmsysProcess_GetExceptionString(cp) << std::endl;
        result = 1;
        break;
      case cmsysProcess_State_Error:
        std::cerr << "Error running link command: "
                  << cmsysProcess_GetErrorString(cp) << std::endl;
        result = 2;
        break;
      default:
        break;
      };
    }


  cmsysProcess_Delete(cp);


  return result;
}
