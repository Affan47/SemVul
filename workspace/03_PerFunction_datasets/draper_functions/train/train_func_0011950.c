translate(const std::string& str) {
  std::string::size_type loc = str.find("_", 0);
  if (loc != std::string::npos) {
    std::string l(str, 0, loc);
    std::string c(str, ++loc);

    std::map<std::string, std::string>::iterator iter1 = _lang_codes.find(l);
    std::map<std::string, std::string>::iterator iter2 = _country_codes.find(c);

    if ((iter1 != _lang_codes.end()) && (iter2 != _country_codes.end())) {
      return Utils::substitute(_("%s (%s)"), iter1->second, iter2->second);
    }
    else {
      return str;
    }
  }
  else {
    std::map<std::string, std::string>::iterator iter = _lang_codes.find(str);
    if (iter == _lang_codes.end()) {
      return str;
    }
    else {
      return iter->second;
    }
  }

  std::map<std::string, std::string>::iterator iter = _lang_codes.find(str);
  if (iter == _lang_codes.end()) {
    return str;
  }

  return iter->second;
}
