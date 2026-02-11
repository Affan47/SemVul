GetFilenamePath(const kwsys_stl::string& filename)
{
  kwsys_stl::string fn = filename;
  SystemTools::ConvertToUnixSlashes(fn);

  kwsys_stl::string::size_type slash_pos = fn.rfind("/");
  if(slash_pos != kwsys_stl::string::npos)
    {
    kwsys_stl::string  ret = fn.substr(0, slash_pos);
    if(ret.size() == 2 && ret[1] == ':')
      {
      return ret + '/';
      }
    if(ret.size() == 0)
      {
      return "/";
      }
    return ret;
    }
  else
    {
    return "";
    }
}
