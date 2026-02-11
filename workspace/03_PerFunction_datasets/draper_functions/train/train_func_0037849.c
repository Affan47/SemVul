BuildCommandLine(
                                    const std::vector<std::string> &cmdLines)
{


  if (cmdLines.empty())
#ifdef _WIN32
    return "cd .";
#else
    return ":";
#endif

  cmOStringStream cmd;
  for (std::vector<std::string>::const_iterator li = cmdLines.begin();
       li != cmdLines.end(); ++li) {
    if (li != cmdLines.begin()) {
      cmd << " && ";
#ifdef _WIN32
    } else if (cmdLines.size() > 1) {
      cmd << "cmd.exe /c ";
#endif
    }
    cmd << *li;
  }
  return cmd.str();
}
