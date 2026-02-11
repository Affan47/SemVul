load(const std::string& name,bool probe)
{
  if (!Glib::Module::get_supported()) {
    return NULL;
  }

  {
    Glib::Mutex::Lock lock(mlock);
    plugin_cache_t::iterator p = plugin_cache.find(name);
    if (p != plugin_cache.end()) {
      ModuleManager::logger.msg(DEBUG, "Found %s in cache", name);
      p->second.load();
      return static_cast<Glib::Module*>(p->second);
    }
  }
  std::string path = findLocation(name);
  if(path.empty()) {
    ModuleManager::logger.msg(VERBOSE, "Could not locate module %s in following paths:", name);
    Glib::Mutex::Lock lock(mlock);
    std::list<std::string>::const_iterator i = plugin_dir.begin();
    for (; i != plugin_dir.end(); i++) {
      ModuleManager::logger.msg(VERBOSE, "\t%s", *i);
    }
    return NULL;
  };

  Glib::Mutex::Lock lock(mlock);
  Glib::ModuleFlags flags = Glib::ModuleFlags(0);
  if(probe) flags|=Glib::MODULE_BIND_LAZY;
  Glib::Module *module = new Glib::Module(path,flags);
  if ((!module) || (!(*module))) {
    ModuleManager::logger.msg(ERROR, strip_newline(Glib::Module::get_last_error()));
    if(module) delete module;
    return NULL;
  }
  ModuleManager::logger.msg(DEBUG, "Loaded %s", path);
  (plugin_cache[name] = module).load();
  void* func = NULL;
  if(!module->get_symbol(ARC_MODULE_CONSTRUCTOR_SYMB,func)) func = NULL;
  if(func) {
    plugin_cache[name].use();
    lock.release();
    (*(arc_module_constructor_func)func)(module,this);
    lock.acquire();
    plugin_cache[name].unuse();
  }
  return module;
}
