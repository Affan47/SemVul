enum_modules(void *cbck, char *item_name, char *item_path)
{
	ModuleInstance *inst;
#if CHECK_MODULE
	QueryInterface query_func;
	LoadInterface load_func;
	ShutdownInterface del_func;
#ifdef WIN32
	HMODULE ModuleLib;
#else
	void *ModuleLib;
	s32 _flags;
#endif

#endif

	GF_ModuleManager *pm = cbck;

	if (strstr(item_name, "nposmozilla")) return 0;
	if (strncmp(item_name, "gm_", 3) && strncmp(item_name, "libgm_", 6)) return 0;
	if (gf_module_is_loaded(pm, item_name) ) return 0;

#if CHECK_MODULE

#ifdef WIN32
	ModuleLib = LoadLibrary(item_path);
	if (!ModuleLib) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("[Core] Cannot load module file %s\n", item_name));
		return 0;
	}

#ifdef _WIN32_WCE
	query_func = (QueryInterface) GetProcAddress(ModuleLib, _T("QueryInterface"));
	load_func = (LoadInterface) GetProcAddress(ModuleLib, _T("LoadInterface"));
	del_func = (ShutdownInterface) GetProcAddress(ModuleLib, _T("ShutdownInterface"));
#else
	query_func = (QueryInterface) GetProcAddress(ModuleLib, "QueryInterface");
	load_func = (LoadInterface) GetProcAddress(ModuleLib, "LoadInterface");
	del_func = (ShutdownInterface) GetProcAddress(ModuleLib, "ShutdownInterface");
#endif
	FreeLibrary(ModuleLib);

#else

#ifdef RTLD_GLOBAL
	_flags =RTLD_LAZY | RTLD_GLOBAL;
#else
	_flags =RTLD_LAZY;
#endif

	ModuleLib = dlopen(item_name, _flags);
        if (!ModuleLib) {
                GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("[Core] Cannot load module file %s, error is %s\n", item_name, dlerror()));
                goto next;
        }

	query_func = (QueryInterface) dlsym(ModuleLib, "QueryInterface");
	load_func = (LoadInterface) dlsym(ModuleLib, "LoadInterface");
	del_func = (ShutdownInterface) dlsym(ModuleLib, "ShutdownInterface");
	dlclose(ModuleLib);
#endif

	if (!load_func || !query_func || !del_func){
          GF_LOG(GF_LOG_WARNING, GF_LOG_CORE,
                 ("[Core] Could not find some signatures in module %s: QueryInterface=%p, LoadInterface=%p, ShutdownInterface=%p\n",
                  item_name, load_func, query_func, del_func));
          return 0;
        }
#endif


	GF_SAFEALLOC(inst, ModuleInstance);
	inst->interfaces = gf_list_new();
	inst->plugman = pm;
	inst->name = gf_strdup(item_name);
        GF_LOG(GF_LOG_INFO, GF_LOG_CORE, ("[Core] Added module %s.\n", inst->name));
	gf_list_add(pm->plug_list, inst);
	return 0;
}
