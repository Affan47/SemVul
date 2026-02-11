tlog3a_xgcb_version(const char* args, const char** unused)
{
  if (strcmp(args, "1") != 0) {
    fatal(MYNAME ": Unsupported file version '%s'!\n", args);
  }
}
