find_matching(const std::string& s, int start, char open, char close) {

  int count = 0;
  for (int i = start; i < s.length(); i++) {
    if (s[i] == close) {
      if (count == 1) {

        return i;
      }
      else count--;
    } else if (s[i] == open) {
      count++;
    }
  }
  LOG(WARNING) << "error in brackets";
  return -1;
}
