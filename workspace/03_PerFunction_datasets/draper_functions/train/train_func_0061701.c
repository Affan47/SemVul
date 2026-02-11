readfile(const std::string& filename) {


  std::ifstream ifs(filename.c_str(), std::ios::in | std::ios::ate);
  if(!ifs.is_open()) {
    T_ERROR("Could not open shader '%s'", filename.c_str());
    throw std::runtime_error("file could not be opened");
  }
  std::ifstream::pos_type len = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  std::vector<char> file(size_t(len+std::ifstream::pos_type(1)), 0);
  size_t offset=0;
  do {
    std::streamsize length = std::streamsize(len) - std::streamsize(offset);
    ifs.read(&file[offset], length);
    offset += size_t(ifs.gcount());
  } while(!ifs.eof() && std::ifstream::pos_type(offset) < len);
  ifs.close();

  return std::string(&file[0]);
}
