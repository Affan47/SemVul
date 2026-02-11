confirmPlugin(Plugin *p) {
        ImageEffectPlugin *plugin = dynamic_cast<ImageEffectPlugin*>(p);
        if (!plugin) {
          return;
        }
        _plugins.push_back(plugin);

        if (_pluginsByID.find(plugin->getIdentifier()) != _pluginsByID.end()) {
          ImageEffectPlugin *otherPlugin = _pluginsByID[plugin->getIdentifier()];
          if (plugin->trumps(otherPlugin)) {
            _pluginsByID[plugin->getIdentifier()] = plugin;
          }
        } else {
          _pluginsByID[plugin->getIdentifier()] = plugin;
        }

        MajorPlugin maj(plugin);

        if (_pluginsByIDMajor.find(maj) != _pluginsByIDMajor.end()) {
          ImageEffectPlugin *otherPlugin = _pluginsByIDMajor[maj];
          if (plugin->trumps(otherPlugin)) {
            _pluginsByIDMajor[maj] = plugin;
          }
        } else {
          _pluginsByIDMajor[maj] = plugin;
        }
      }
