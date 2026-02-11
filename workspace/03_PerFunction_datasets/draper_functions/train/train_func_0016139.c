getValue(NPP instance, NPPVariable variable, void *value) {
	inst = instance;
	switch(variable) {
	default:
		if (Log::enabledDbg()) Log::dbg("getValue - default");
		return NPERR_GENERIC_ERROR;
	case NPPVpluginNameString:
        if (Log::enabledDbg()) Log::dbg("getvalue - name string");
		*((const char **)value) = pluginName;
		break;
	case NPPVpluginDescriptionString:
        if (Log::enabledDbg()) Log::dbg("getvalue - description string");
		*((const char **)value) = pluginDescription;
		break;
	case NPPVpluginScriptableNPObject:
        if (Log::enabledDbg()) Log::dbg("getvalue - scriptable object");
		if(!so) {
			so = npnfuncs->createobject(instance, &npcRefObject);
		}
        npnfuncs->retainobject(so);
		*(NPObject **)value = so;
		break;
	case NPPVpluginNeedsXEmbed:
        if (Log::enabledDbg()) Log::dbg("getvalue - xembed");
		*((bool *)value) = supportsXEmbed;
		break;
	}
	return NPERR_NO_ERROR;
}
