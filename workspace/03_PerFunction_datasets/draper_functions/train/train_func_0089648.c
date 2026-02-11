CreateCDCommand(std::vector<std::string>& commands, const char *tgtDir,
                  cmLocalGenerator::RelativeRoot relRetDir)
{
  const char* retDir = this->GetRelativeRootPath(relRetDir);


  if (!strcmp(tgtDir,retDir))
    {
    return;
    }


  const char* cd_cmd = this->MinGWMake? "cd /d " : "cd ";

  if(!this->UnixCD)
    {


    std::string cmd = cd_cmd;
    cmd += this->ConvertToOutputForExisting(tgtDir, relRetDir);
    commands.insert(commands.begin(),cmd);


    cmd = cd_cmd;
    cmd += this->ConvertToOutputForExisting(relRetDir, tgtDir);
    commands.push_back(cmd);
    }
  else
    {


    std::vector<std::string>::iterator i = commands.begin();
    for (; i != commands.end(); ++i)
      {
      std::string cmd = cd_cmd;
      cmd += this->ConvertToOutputForExisting(tgtDir, relRetDir);
      cmd += " && ";
      cmd += *i;
      *i = cmd;
      }
    }
}
