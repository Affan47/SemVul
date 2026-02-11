CheckUnPutEnv(const char* env, const char* name)
{
  if(!kwsys::SystemTools::UnPutEnv(env))
    {
    kwsys_ios::cerr << "UnPutEnv(\"" << env << "\") failed!"
                    << kwsys_ios::endl;
    return false;
    }
  if(const char* v = kwsys::SystemTools::GetEnv(name))
    {
    kwsys_ios::cerr << "GetEnv(\"" << name << "\") returned \""
                    << v << "\", not (null)!" << kwsys_ios::endl;
    return false;
    }
  return true;
}
