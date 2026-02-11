compareDN(const std::string& dn1, const std::string& dn2) {
    std::list<std::string> dnl1;
    std::list<std::string> dnl2;
    if(!decodeDN(dn1,dnl1)) return false;
    if(!decodeDN(dn2,dnl2)) return false;
    return compareDN(dnl1,dnl2);
  }
