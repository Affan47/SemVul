BlockStart(const std::string& id, const std::string& name) {
    if(map_) return true;
    std::string bname = id;
    if(!name.empty()) bname = bname+"/"+name;
    if(file_.blocknames.empty()) {
      is_block_ = true;
      return true;
    };
    for(std::list<std::string>::const_iterator block = file_.blocknames.begin();
                                 block != file_.blocknames.end();++block) {
      if(*block == bname) {
        is_block_ = true;
        break;
      };
    };
    return true;
  }
