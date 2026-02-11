NPP_SetWindow (NPP instance, NPWindow* pNPWindow)
{
    if (!instance) {
        return NPERR_INVALID_INSTANCE_ERROR;
    }

    if (!pNPWindow) {
        return NPERR_GENERIC_ERROR;
    }

    nsPluginInstanceBase * plugin = (nsPluginInstanceBase *)instance->pdata;

    if (!plugin) {
        return NPERR_GENERIC_ERROR;
    }


    if (!plugin->isInitialized() && pNPWindow->window) {
        if (!plugin->init(pNPWindow)) {
            NS_DestroyPluginInstance(plugin);
            return NPERR_MODULE_LOAD_FAILED_ERROR;
        }
    }


    if (!pNPWindow->window && plugin->isInitialized()) {
        return plugin->SetWindow(pNPWindow);
    }


    if (plugin->isInitialized() && pNPWindow->window) {
        return plugin->SetWindow(pNPWindow);
    }


    if (!pNPWindow->window && !plugin->isInitialized()) {
        return plugin->SetWindow(pNPWindow);
    }

    return NPERR_NO_ERROR;
}
