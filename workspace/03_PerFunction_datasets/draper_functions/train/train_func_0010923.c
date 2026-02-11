getCacheDirectory(FXbool create) {
  FXString xdg_cache_home = FXSystem::getEnvironment("XDG_CACHE_HOME");
  if (xdg_cache_home.empty())
    xdg_cache_home=FXSystem::getHomeDirectory()+PATHSEPSTRING ".cache" ;

  xdg_cache_home+=PATHSEPSTRING "gogglesmm";

  if (create)
    gm_make_path(xdg_cache_home);

  return xdg_cache_home;
  }
