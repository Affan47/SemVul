__arc_init(void) {

  Glib::Module* module = NULL;
  std::string modulepath;
#ifdef _MACOSX


  modulepath = std::string("libjarc.")+".jnilib";
#else
  modulepath = std::string("libjarc.")+G_MODULE_SUFFIX;
#endif
#ifdef HAVE_GLIBMM_BIND_LOCAL
  module = new Glib::Module(modulepath,Glib::ModuleFlags(0));
#else
  module = new Glib::Module(modulepath);
#endif
  if(module != NULL) {
    if(*module) return;
    delete module;
  };
  Arc::Logger::getRootLogger().msg(Arc::WARNING,"Failed to export symbols of ARC java module");
}
