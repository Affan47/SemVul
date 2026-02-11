FilterByKind(const std::string& kind, std::list<ModuleDesc>& mdescs) {
    for (std::list<ModuleDesc>::iterator mdesc = mdescs.begin();
         mdesc != mdescs.end();) {
      for (std::list<PluginDesc>::iterator pdesc = mdesc->plugins.begin(); pdesc != mdesc->plugins.end();) {
        if (pdesc->kind != kind) {

          pdesc = mdesc->plugins.erase(pdesc);
        }
        else {
          pdesc++;
        }
      }

      if (mdesc->plugins.empty()) {

        mdesc = mdescs.erase(mdesc);
      }
      else {
        mdesc++;
      }
    }
  }
