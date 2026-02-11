loadPlugin(const char* path)
{
#ifdef SEEXPR_WIN32
    std::cerr<<"SeExpr: warning Plugins are not supported on windows currently"<<std::endl;
#else
    void* handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
	std::cerr << "Error reading expression plugin: " << path << std::endl;
	const char* err = dlerror();
	if (err) std::cerr << err << std::endl;
	return;
    }
    typedef void (*initfn_v1) (SeExprFunc::Define);
    initfn_v1 init_v1 = (initfn_v1) dlsym(handle, "SeExprPluginInit");
    typedef void (*initfn_v2) (SeExprFunc::Define3);
    initfn_v2 init_v2 = (initfn_v2) dlsym(handle, "SeExprPluginInitV2");

    if(init_v2){
        init_v2(defineInternal3);
        Functions.addLibraryReference(handle);
    }else if(init_v1){
        init_v1(defineInternal);
        Functions.addLibraryReference(handle);
    }else{
	std::cerr << "Error reading expression plugin: " << path << std::endl;
	std::cerr << "No function named SeExprPluginInit or SeExprPluginInitV2 found" << std::endl;
	dlclose(handle);
	return;
    }
#endif
}
