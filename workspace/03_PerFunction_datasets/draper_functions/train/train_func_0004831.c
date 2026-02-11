fill_data_dir(const Config * config, String & dir1, String & dir2) {
    if (config->have("local-data-dir")) {
      dir1 = config->retrieve("local-data-dir");
      if (dir1[dir1.size()-1] != '/') dir1 += '/';
    } else {
      dir1 = config->retrieve("master-path");
      size_t pos = dir1.rfind('/');
      if (pos != String::npos)
        dir1.resize(pos + 1);
      else
        dir1 = "./";
    }
    dir2 = config->retrieve("data-dir");
    if (dir2[dir2.size()-1] != '/') dir2 += '/';
  }
