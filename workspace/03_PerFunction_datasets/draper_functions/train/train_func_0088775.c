isnic(char ch)
{

  static std::string nic("\"\'\\@<>!$%&{}[]");
  return ch<0 || nic.find(ch)!=std::string::npos;
}
