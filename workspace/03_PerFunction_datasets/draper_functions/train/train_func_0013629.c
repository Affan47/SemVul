AddDefines(const std::vector<std::string>& defines) {
  for (auto define = defines.cbegin(); define != defines.cend(); define++)
    AddDefine(*define);
}
