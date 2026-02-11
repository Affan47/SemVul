LoadPlugIn (std::string filename)
{
	WoklibPlugin *plugin;
	WoklibPlugin *(*mkr) (WLSignal *wls);

#ifdef __WIN32
    HINSTANCE hLib=LoadLibrary(filename.c_str());
    if (!hLib)
	{
		woklib_error(wls, "Cannot load library");
		return 0;
	}

	mkr = (WoklibPlugin *(*)(WLSignal *wls)) GetProcAddress((HMODULE)hLib, "maker");

    if ( mkr == NULL )
    {
        std::cout << "Unable to load the function" << std::endl;
        return 0;
    }

	plugin = mkr (wls);

	pluginhandle[filename] = hLib;
	plugins[filename] = plugin;

#else
	void *PlugInLib = dlopen (filename.c_str (), RTLD_LOCAL|RTLD_LAZY);
	if (!PlugInLib)
	{

		std::cerr << "Cannot load library: " << dlerror() << std::endl;
		return 0;
	}

	mkr = (WoklibPlugin *(*)(WLSignal *wls)) dlsym (PlugInLib, "maker");

	plugin = mkr (wls);

	pluginhandle[filename] = PlugInLib;
	plugins[filename] = plugin;
#endif
	return 1;
}
