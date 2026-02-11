UT_addOrReplacePathSuffix(std::string & sPath, const char * sSuffix)
{
  UT_sint32 i = sPath.length() - 1;
  const char *sSlash = "/";
  const char *sBSlash = "\\";
  const char *sDot = ".";
  std::string s = sPath.substr(i,1);
  while(i>0 &&  (s != sDot) && (s!= sBSlash) && (s!=sSlash))
  {
      i -=1;
      s = sPath.substr(i,1);
  }
  if((s == sSlash) || (s == sBSlash) || (i<=0))
  {
      sPath += sSuffix;
  }
  else
  {
      std::string sLeader = sPath.substr(0,i);
      sPath = sLeader;
      sPath += sSuffix;
  }
  return true;
}
