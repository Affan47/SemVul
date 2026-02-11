CreateURL(std::string str) {
    std::string::size_type pos1 = str.find("://");
    if (pos1 == std::string::npos) {
      str = "https://" + str;
      pos1 = 5;
    } else {
      if(lower(str.substr(0,pos1)) != "https" && lower(str.substr(0,pos1)) != "http" ) return URL();
    }
    std::string::size_type pos2 = str.find(":", pos1 + 3);
    std::string::size_type pos3 = str.find("/", pos1 + 3);
    if (pos3 == std::string::npos && pos2 == std::string::npos) str += ":8443";
    else if (pos2 == std::string::npos || pos2 > pos3) str.insert(pos3, ":8443");

    return str;
  }
