SystemToolsAppendComponents(
  kwsys_stl::vector<kwsys_stl::string>& out_components,
  kwsys_stl::vector<kwsys_stl::string>::const_iterator first,
  kwsys_stl::vector<kwsys_stl::string>::const_iterator last)
{
  for(kwsys_stl::vector<kwsys_stl::string>::const_iterator i = first;
      i != last; ++i)
    {
    if(*i == "..")
      {
      if(out_components.begin() != out_components.end())
        {
        out_components.erase(out_components.end()-1, out_components.end());
        }
      }
    else if(!(*i == ".") && !(*i == ""))
      {
      out_components.push_back(*i);
      }
    }
}
