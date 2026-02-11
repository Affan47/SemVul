str() const {
    std::string capabilities = "";
    if (!Capability.empty()) {
      capabilities = ", capabilities:";
      for (std::set<std::string>::const_iterator it = Capability.begin(); it != Capability.end(); it++) {
        capabilities = capabilities + " " + *it;
      }
    }
    std::string interfaceNameToPrint = "<empty InterfaceName>";
    if (!InterfaceName.empty()) {
      interfaceNameToPrint = InterfaceName;
    }
    return URLString + " (" + interfaceNameToPrint + capabilities + ")";
  }
