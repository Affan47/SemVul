isExternallyVisible(const GlobalValue &GV,
                                const std::set<std::string> &ExternalNames) {

  if (GV.isDeclaration())
    return true;


  if (GV.hasAvailableExternallyLinkage())
    return true;


  if (GV.hasDLLExportStorageClass())
    return true;


  if (!GV.hasLocalLinkage() && ExternalNames.count(GV.getName()))
    return true;

  return false;
}
