enumeratePlugins(PluginKey forPlugin)
{
    vector<string> path = PluginHostAdapter::getPluginPath();

    string libraryName, identifier;
    if (forPlugin != "") {
        if (!decomposePluginKey(forPlugin, libraryName, identifier)) {
            std::cerr << "WARNING: Vamp::HostExt::PluginLoader: Invalid plugin key \""
                      << forPlugin << "\" in enumerate" << std::endl;
            return;
        }
    }

    for (size_t i = 0; i < path.size(); ++i) {

        vector<string> files = listFiles(path[i], PLUGIN_SUFFIX);

        for (vector<string>::iterator fi = files.begin();
             fi != files.end(); ++fi) {

            if (libraryName != "") {


                string temp = *fi;
                for (size_t i = 0; i < temp.length(); ++i) {
                    temp[i] = tolower(temp[i]);
                }
                string::size_type pi = temp.find('.');
                if (pi == string::npos) {
                    if (libraryName != temp) continue;
                } else {
                    if (libraryName != temp.substr(0, pi)) continue;
                }
            }

            string fullPath = path[i];
            fullPath = splicePath(fullPath, *fi);
            void *handle = loadLibrary(fullPath);
            if (!handle) continue;

            VampGetPluginDescriptorFunction fn =
                (VampGetPluginDescriptorFunction)lookupInLibrary
                (handle, "vampGetPluginDescriptor");

            if (!fn) {
                if (forPlugin != "") {
                    cerr << "Vamp::HostExt::PluginLoader: No vampGetPluginDescriptor function found in library \""
                         << fullPath << "\"" << endl;
                }
                unloadLibrary(handle);
                continue;
            }

            int index = 0;
            const VampPluginDescriptor *descriptor = 0;
            bool found = false;

            while ((descriptor = fn(VAMP_API_VERSION, index))) {
                ++index;
                if (identifier != "") {
                    if (descriptor->identifier != identifier) continue;
                }

                found = true;
                PluginKey key = composePluginKey(*fi, descriptor->identifier);

                if (m_pluginLibraryNameMap.find(key) ==
                    m_pluginLibraryNameMap.end()) {
                    m_pluginLibraryNameMap[key] = fullPath;
                }
            }

            if (!found && forPlugin != "") {
                cerr << "Vamp::HostExt::PluginLoader: Plugin \""
                     << identifier << "\" not found in library \""
                     << fullPath << "\"" << endl;
            }

            unloadLibrary(handle);
        }
    }

    if (forPlugin == "") m_allPluginsEnumerated = true;
}
