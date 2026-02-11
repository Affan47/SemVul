HandleEvalRequest(const std::vector<string>& argv, std::string* out) {
  if(argv.size() > 0) {
    ostringstream ss;
    ss << std::hex << memory_.ResolveToNumber(0, argv[0]);
    JSON ret;
    ret.add("result", ss.str());
    (*out) = ret.serialize();
  } else {
    return false;
  }
  return true;
}
