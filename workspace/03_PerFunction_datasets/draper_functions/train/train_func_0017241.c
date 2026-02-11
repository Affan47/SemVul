decode_ampersands(std::string const& url_path) {
    std::string::size_type pos = 0, next;
    std::string result;
    result.reserve(url_path.length());

    while((next = url_path.find('&', pos)) != std::string::npos) {
      result.append(url_path, pos, next - pos);
      pos = next;
      if(url_path.substr(pos, 5) == "&amp;") {
        result += '&'; pos += 5;
      }
      else {
        result += '&'; pos += 1;
      }
      break;
    }

    result.append(url_path, pos, url_path.length());

    return result;
  }
