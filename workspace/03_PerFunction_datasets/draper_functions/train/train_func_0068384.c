FindTopDir()
{
  std::string top_dir = this->SourceDirectory;


  const char* git = this->CommandLineTool.c_str();
  char const* git_rev_parse[] = {git, "rev-parse", "--show-cdup", 0};
  std::string cdup;
  OneLineParser rev_parse_out(this, "rev-parse-out> ", cdup);
  OutputLogger rev_parse_err(this->Log, "rev-parse-err> ");
  if(this->RunChild(git_rev_parse, &rev_parse_out, &rev_parse_err) &&
     !cdup.empty())
    {
    top_dir += "/";
    top_dir += cdup;
    top_dir = cmSystemTools::CollapseFullPath(top_dir.c_str());
    }
  return top_dir;
}
