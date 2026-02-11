Rewrite(string *out, const StringPiece &rewrite,
                 const StringPiece *vec, int veclen) const {
  for (const char *s = rewrite.data(), *end = s + rewrite.size();
       s < end; s++) {
    int c = *s;
    if (c == '\\') {
      s++;
      c = (s < end) ? *s : -1;
      if (isdigit(c)) {
        int n = (c - '0');
        if (n >= veclen) {
          if (options_.log_errors()) {
            LOG(ERROR) << "requested group " << n
                       << " in regexp " << rewrite.data();
          }
          return false;
        }
        StringPiece snip = vec[n];
        if (snip.size() > 0)
          out->append(snip.data(), snip.size());
      } else if (c == '\\') {
        out->push_back('\\');
      } else {
        if (options_.log_errors())
          LOG(ERROR) << "invalid rewrite pattern: " << rewrite.data();
        return false;
      }
    } else {
      out->push_back(c);
    }
  }
  return true;
}
