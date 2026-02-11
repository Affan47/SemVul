Umatch(const std::string& str1, const std::string& str2)
{
  CS cmd(CS::_STRING, str1);
  if (cmd.umatch(str2)) {
    return true;
  }else{
    return 0;
  }
}
