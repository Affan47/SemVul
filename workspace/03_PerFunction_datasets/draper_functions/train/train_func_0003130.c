NewPILInterface(PILInterfaceType*	interfacetype
	,	const char*	interfacename
	,	void *		exports
	,	PILInterfaceFun	closefun
	,	void*		ud_interface
	,	PILPlugin*	loading_plugin)
{
	PILInterface*	ret = NULL;
	PILInterface*	look = NULL;


	if ((look = g_hash_table_lookup(interfacetype->interfaces
	,	interfacename)) != NULL) {
		PILLog(PIL_DEBUG, "Deleting PILInterface!");
		DelPILInterface(look);
	}
	ret = NEW(PILInterface);
	STATNEW(interface);
	if (DEBUGPLUGIN) {
		PILLog(PIL_DEBUG, "NewPILInterface(0x%x)", (unsigned long)ret);
	}

	if (ret) {
		ret->MagicNum = PIL_MAGIC_INTERFACE;
		ret->interfacetype = interfacetype;
		ret->exports = exports;
		ret->ud_interface = ud_interface;
		ret->interfacename = g_strdup(interfacename);
		ret->ifmanager = interfacetype->ifmgr_ref;
		ret->loadingpi = loading_plugin;
		g_hash_table_insert(interfacetype->interfaces
		,	g_strdup(ret->interfacename), ret);

		ret->if_close = closefun;
		ret->refcnt = 1;
		if (DEBUGPLUGIN) {
			PILLog(PIL_DEBUG, "NewPILInterface(0x%lx:%s/%s)*** user_data: 0x%lx *******"
			,	(unsigned long)ret
			,	interfacetype->typename
			,	ret->interfacename
			,	ud_interface);
		}
	}
	return ret;
}
