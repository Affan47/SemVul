tokenize(const std::string & line,
                              const char & delim) {
  StringVectorT retval;

  std::istringstream iss(line);
  std::string fragment;
  while(std::getline(iss, fragment, delim)) {
    retval.push_back(fragment);
  }

  return retval;
}
