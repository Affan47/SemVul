get_filepath_with_extension(const std::string& filepath, const std::string& extension)
{
  std::string result = filepath;

  bool add_ext = false;
  const std::string str_ext = "." + extension;

  if(result.size() < str_ext.size())
  {
    add_ext = true;
  }
  else
  {
    const Glib::ustring strEnd = result.substr(result.size() - str_ext.size());
    if(strEnd != str_ext)
      add_ext = true;
  }


  if(add_ext)
    result += str_ext;


  return result;
}
