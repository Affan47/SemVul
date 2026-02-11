xfile_error(const char *msg) const
{
  errormsg_with_errno("%s: %s", name.xfile().c_str(), msg);
}
