MakeConfig(XMLNode cfg) const {
    XMLNode mm = BaseConfig::MakeConfig(cfg);
    std::list<std::string> mccs;
    for (std::list<std::string>::const_iterator path = plugin_paths.begin();
         path != plugin_paths.end(); path++) {
      try {
        Glib::Dir dir(*path);
        for (Glib::DirIterator file = dir.begin(); file != dir.end(); file++) {
          if ((*file).substr(0, 6) == "libmcc") {
            std::string name = (*file).substr(6, (*file).find('.') - 6);
            if (std::find(mccs.begin(), mccs.end(), name) == mccs.end()) {
              mccs.push_back(name);
              cfg.NewChild("Plugins").NewChild("Name") = "mcc" + name;
            }
          }


        }
      }
      catch (Glib::FileError&) {}
    }
    return mm;
  }
