as(UrlMap& m, const char* label, const char* s,
          bool expectFailure = false) {
    vector<string> value;
    ConfigFile::split(value, s, 0);
    const char* result = m.addServer(base, label, value);
    if (result != 0) msg("addServer: %1", result);
    Assert(expectFailure == (result != 0));
  }
