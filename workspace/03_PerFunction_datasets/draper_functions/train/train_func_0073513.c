load(const char *modName,
						     ArRobot *robot,
						     void *modArgument,
						     bool quiet)
{
  std::string name;
  std::map<std::string, DllRef>::iterator iter;
  DllRef handle;
  typedef bool(*TFunc)(ArRobot*,void*);
  TFunc func;
  bool ret;

  name=modName;
#ifdef WIN32
  if (strstr(modName, ".dll") == 0)
    name+=".dll";
#else
  if (strstr(modName, ".so") == 0)
    name+=".so";
#endif

  iter=ourModMap.find(name);
  if (iter != ourModMap.end())
    return(STATUS_ALREADY_LOADED);

  handle=dlopen(name.c_str(), RTLD_NOW | RTLD_GLOBAL);

  if (!handle || dlerror() != NULL)
  {
    if (!quiet)
      ArLog::log(ArLog::Terse, "Failure to load module '%s': %s",
		 name.c_str(), dlerror());
    return(STATUS_FAILED_OPEN);
  }

#ifndef _MSC_VER
  #pragma GCC diagnostic push

#endif

  func=reinterpret_cast<TFunc>( dlsym(handle, "ariaInitModule") );
#ifndef _MSC_VER
  #pragma GCC diagnostic pop
#endif
  if (!func || dlerror() != NULL)
  {
    if (!quiet)
      ArLog::log(ArLog::Terse, "No module initializer for %s.", modName);
    ourModMap.insert(std::map<std::string, DllRef>::value_type(name,
							       handle));
    return(STATUS_SUCCESS);


  }
  ret=(*func)(robot, modArgument);

  if (ret)
  {
    ourModMap.insert(std::map<std::string, DllRef>::value_type(name,
							       handle));
    return(STATUS_SUCCESS);
  }
  else
  {
    if (!quiet)
      ArLog::log(ArLog::Terse, "Module '%s' failed its init sequence",
		 name.c_str());
    dlclose(handle);
    return(STATUS_INIT_FAILED);
  }
}
