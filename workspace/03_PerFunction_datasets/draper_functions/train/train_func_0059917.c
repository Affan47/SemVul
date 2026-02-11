VisualStudioLink(std::vector<std::string>& args, int type)
{
  if(args.size() < 2)
    {
    return -1;
    }
  bool verbose = false;
  if(cmSystemTools::GetEnv("VERBOSE"))
    {
    verbose = true;
    }
  std::vector<std::string> expandedArgs;
  for(std::vector<std::string>::iterator i = args.begin();
      i != args.end(); ++i)
    {

    if((*i)[0] == '@' && i->find("@CMakeFiles") != 0 )
      {
      std::ifstream fin(i->substr(1).c_str());
      std::string line;
      while(cmSystemTools::GetLineFromStream(fin,
                                             line))
        {
        cmSystemTools::ParseWindowsCommandLine(line.c_str(), expandedArgs);
        }
      }
    else
      {
      expandedArgs.push_back(*i);
      }
    }
  bool hasIncremental = false;
  bool hasManifest = true;
  for(std::vector<std::string>::iterator i = expandedArgs.begin();
      i != expandedArgs.end(); ++i)
    {
    if(cmSystemTools::Strucmp(i->c_str(), "/INCREMENTAL:YES") == 0)
      {
      hasIncremental = true;
      }
    if(cmSystemTools::Strucmp(i->c_str(), "/MANIFEST:NO") == 0)
      {
      hasManifest = false;
      }
    }
  if(hasIncremental && hasManifest)
    {
    if(verbose)
      {
      std::cout << "Visual Studio Incremental Link with embeded manifests\n";
      }
    return cmake::VisualStudioLinkIncremental(expandedArgs, type, verbose);
    }
  if(verbose)
    {
    if(!hasIncremental)
      {
      std::cout << "Visual Studio Non-Incremental Link\n";
      }
    else
      {
      std::cout << "Visual Studio Incremental Link without manifests\n";
      }
    }
  return cmake::VisualStudioLinkNonIncremental(expandedArgs, type, hasManifest, verbose);
}
