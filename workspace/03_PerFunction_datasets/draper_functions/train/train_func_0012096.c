CheckYesNoCommand(bool& config_param, const std::string& name, std::string& rest) {
  std::string s = config_next_arg(rest);
  if (s == "yes") {
    config_param = true;
  }
  else if(s == "no") {
    config_param = false;
  }
  else {
    logger.msg(Arc::ERROR, "Wrong option in %s", name);
    return false;
  }
  return true;
}
