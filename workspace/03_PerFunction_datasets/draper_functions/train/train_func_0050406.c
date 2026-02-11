basename(const std::string & path)
{
  if(path == "")
  {
    return std::string("");
  }

  std::string::const_reverse_iterator last_slash =
    std::find(
      path.rbegin(),
      path.rend(), '/');
  if( last_slash == path.rend() )
  {

    return path;
  }else if(1 == (last_slash.base() - path.begin()))
  {

    return std::string(path.begin()+1,path.end());
  }else if(path.end() == last_slash.base() )
  {

    std::string redo = std::string(path.begin(),path.end()-1);
    return igl::basename(redo);
  }
  return std::string(last_slash.base(),path.end());
}
