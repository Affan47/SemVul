canonicalizePath(const std::string& path) {
  std::vector<std::string> parts;

  std::string::size_type pos = 0;
  while (pos != std::string::npos) {
    std::string::size_type slashPos = path.find_first_of('/', pos);

    std::string part;
    if (slashPos == std::string::npos) {
      part.assign(path, pos, path.size() - pos);
      pos = slashPos;
    } else {
      part.assign(path, pos, slashPos - pos);
      pos = path.find_first_not_of('/', slashPos);
    }

    if (part.empty() || part == ".") {

    } else if (part == "..") {
      if (parts.empty()) {

      } else {
        parts.pop_back();
      }
    } else {
      parts.push_back(part);
    }
  }

  std::string result;
  result.reserve(path.size());
  for (unsigned int i = 0; i < parts.size(); i++) {
    if (i > 0) {
      result.push_back('/');
    }
    result.append(parts[i]);
  }

  return result;
}
