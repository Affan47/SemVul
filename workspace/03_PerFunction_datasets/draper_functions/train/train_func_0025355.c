Path2BaseDN(const std::string& newpath) {

    if (newpath.empty())
      return "";

    std::string basedn;
    std::string::size_type pos, pos2;

    pos = newpath.size();
    while ((pos2 = newpath.rfind("/", pos - 1)) != std::string::npos) {
      if (pos2 == 0) break;
      basedn += newpath.substr(pos2 + 1, pos - pos2 - 1) + ", ";
      pos = pos2;
    }

    if (pos2 == std::string::npos)
      basedn += newpath.substr(0, pos);
    else
      basedn += newpath.substr(pos2 + 1, pos - pos2 - 1);

    return basedn;
  }
