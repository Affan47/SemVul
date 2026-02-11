MakeValidLatexString(std::string source, std::string& dest) const
  {
    std::string::iterator c;
    for (c=source.begin(); c!=source.end(); c++) {
      if (*c == '_') {
        dest.append("\\_");
      }
      else if (*c == '^') {
        dest.append("\\^");
      }
      else {
        dest += *c;
      }
    }
  }
