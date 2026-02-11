Realpath(const char *path, kwsys_stl::string & resolved_path)
{
  char resolved_name[KWSYS_SYSTEMTOOLS_MAXPATH];

  char *ret = realpath(path, resolved_name);
  if(ret)
    {
    resolved_path = ret;
    }
  else
    {

    resolved_path = path;
    }
}
