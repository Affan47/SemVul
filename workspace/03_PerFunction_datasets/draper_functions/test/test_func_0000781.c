parse_host(const sharp::FileInfo & file_info)
  {
    std::string name = file_info.get_name();
    std::string ext = file_info.get_extension();

    if (ext.empty()) {
      return "";
    }

    int ext_pos = sharp::string_index_of(name, ext);
    if (ext_pos <= 0) {
      return "";
    }

    std::string host = sharp::string_substring(name, 0, ext_pos);
    if (host.empty()) {
      return "";
    }

    return host;
  }
