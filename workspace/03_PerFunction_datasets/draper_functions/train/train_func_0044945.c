convert_to_rdn(const std::string& dn) {
    std::string ret;
    size_t pos1 = std::string::npos;
    size_t pos2;
    do {
      std::string str;
      pos2 = dn.find_last_of("/", pos1);
      if(pos2 != std::string::npos && pos1 == std::string::npos) {
        str = dn.substr(pos2+1);
        ret.append(str);
        pos1 = pos2-1;
      }
      else if (pos2 != std::string::npos && pos1 != std::string::npos) {
        str = dn.substr(pos2+1, pos1-pos2);
        ret.append(str);
        pos1 = pos2-1;
      }
      if(pos2 != (std::string::npos+1)) ret.append(",");
    }while(pos2 != std::string::npos && pos2 != (std::string::npos+1));
    return ret;
  }
