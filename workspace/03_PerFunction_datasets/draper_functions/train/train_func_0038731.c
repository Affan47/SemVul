tokens_to_string(std::vector<std::string> tokens) {
  std::string s;
  for(int n = 0; n<tokens.size(); ++n) {
    s += "\""+tokens[n]+"\" ";
  };
  return s;
}
