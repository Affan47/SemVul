AppendCustomCommandLines(const cmCustomCommand *cc,
                                            std::vector<std::string> &cmdLines)
{
  cmCustomCommandGenerator ccg(*cc, this->GetConfigName(), this->Makefile);
  if (ccg.GetNumberOfCommands() > 0) {
    const char* wd = cc->GetWorkingDirectory();
    if (!wd)
      wd = this->GetMakefile()->GetStartOutputDirectory();

    cmOStringStream cdCmd;
#ifdef _WIN32
        std::string cdStr = "cd /D ";
#else
        std::string cdStr = "cd ";
#endif
    cdCmd << cdStr << this->ConvertToOutputFormat(wd, SHELL);
    cmdLines.push_back(cdCmd.str());
  }
  for (unsigned i = 0; i != ccg.GetNumberOfCommands(); ++i) {
    cmdLines.push_back(this->ConvertToOutputFormat(ccg.GetCommand(i).c_str(),
                                                   SHELL));
    std::string& cmd = cmdLines.back();
    ccg.AppendArguments(i, cmd);
  }
}
