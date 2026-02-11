CleanupImpl()
{
  std::vector<const char*> svn_cleanup;
  svn_cleanup.push_back("cleanup");
  OutputLogger out(this->Log, "cleanup-out> ");
  OutputLogger err(this->Log, "cleanup-err> ");
  this->RunSVNCommand(svn_cleanup, &out, &err);
}
