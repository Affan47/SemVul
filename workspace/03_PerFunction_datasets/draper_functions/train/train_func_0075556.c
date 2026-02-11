convert_from(const Glib::ustring& in, std::string& out, int enc) {
  if (enc == utf8()) {
    out = in;
    return enc;
  }

  std::string err;
  if (convert(in, out, utf8(), enc, err)) {
    return enc;
  }
  out = err;
  return -1;
}
