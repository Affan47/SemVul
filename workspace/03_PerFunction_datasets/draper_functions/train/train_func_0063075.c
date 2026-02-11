CreateExtensionRegex(std::vector<std::string> const& exts, LinkType type)
{

  std::string libext = "(";
  const char* sep = "";
  for(std::vector<std::string>::const_iterator i = exts.begin();
      i != exts.end(); ++i)
    {

    libext += sep;
    sep = "|";


    libext += "\\";
#if defined(_WIN32) && !defined(__CYGWIN__)
    libext += this->NoCaseExpression(i->c_str());
#else
    libext += *i;
#endif
    }


  libext += ")";


  if(this->OpenBSD)
    {
    libext += "(\\.[0-9]+\\.[0-9]+)?";
    }
  else if(type == LinkShared)
    {
    libext += "(\\.[0-9]+)?";
    }

  libext += "$";
  return libext;
}
