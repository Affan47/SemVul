BuildMakeCommand(
             const std::string& make, const char* makefile, const char* target)
{
  std::string command = "\"";
  command += make + "\"";
  if (strcmp(this->GlobalGenerator->GetName(), "NMake Makefiles")==0)
    {
    std::string makefileName = cmSystemTools::ConvertToOutputPath(makefile);
    command += ", \"/NOLOGO\", \"/f\", \"";
    command += makefileName + "\"";
    command += ", \"VERBOSE=1\", \"";
    command += target;
    command += "\"";
    }
  else if (strcmp(this->GlobalGenerator->GetName(), "Ninja")==0)
    {
    std::string makefileName = cmSystemTools::ConvertToOutputPath(makefile);
    command += ", \"-f\", \"";
    command += makefileName + "\"";
    command += ", \"-v\", \"";
    command += target;
    command += "\"";
    }
  else
    {
    std::string makefileName;
    if (strcmp(this->GlobalGenerator->GetName(), "MinGW Makefiles")==0)
      {


        makefileName = makefile;
      }
      else
      {
        makefileName = cmSystemTools::ConvertToOutputPath(makefile);
      }
    command += ", \"-f\", \"";
    command += makefileName + "\"";
    command += ", \"VERBOSE=1\", \"";
    command += target;
    command += "\"";
    }
  return command;
}
