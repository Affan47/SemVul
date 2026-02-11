NormalGetFullPath(const char* config, bool implib,
                                        bool realname)
{

  std::string fpath = this->GetDirectory(config, implib);
  fpath += "/";

  if(this->IsAppBundleOnApple())
    {
    fpath += this->GetFullName(config, false);
    fpath += ".app/Contents/MacOS/";
    }
  if(this->IsFrameworkOnApple())
    {
    fpath += this->GetFullName(config, false);
    fpath += ".framework/Versions/";
    fpath += this->GetFrameworkVersion();
    fpath += "/";
    }


  if(implib)
    {
    fpath += this->GetFullName(config, true);
    }
  else if(realname)
    {
    fpath += this->NormalGetRealName(config);
    }
  else
    {
    fpath += this->GetFullName(config, false);
    }
  return fpath;
}
