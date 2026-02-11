GetWorkingRevision()
{

  const char* git = this->CommandLineTool.c_str();
  const char* git_rev_list[] = {git, "rev-list", "-n", "1", "HEAD", 0};
  std::string rev;
  OneLineParser out(this, "rl-out> ", rev);
  OutputLogger err(this->Log, "rl-err> ");
  this->RunChild(git_rev_list, &out, &err);
  return rev;
}
