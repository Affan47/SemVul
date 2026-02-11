file_user_list(const std::string& path,std::string &ulist) {
    std::ifstream f(path.c_str());
    if(! f.is_open() ) return false;
    for(;f.good();) {
      std::string rest;
      std::getline(f,rest);
      Arc::trim(rest," \t\r\n");
      std::string name = "";
      for(;rest.length() != 0;) {
        name=config_next_arg(rest);
      };
      if(name.length() == 0) continue;
      std::string::size_type pos;
      if((pos=ulist.find(name)) != std::string::npos) {
        if(pos!=0)
          if(ulist[pos-1] != ' ') { ulist+=" "+name; continue; };
        pos+=name.length();
        if(pos < ulist.length())
          if(ulist[pos] != ' ') { ulist+=" "+name; continue; };
      }
      else { ulist+=" "+name; };
    };
    f.close();
    return true;
  }
