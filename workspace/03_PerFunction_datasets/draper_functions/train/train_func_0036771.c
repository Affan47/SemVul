FullPathURIEncoded() const {
    std::string fullpath;

    if (!path.empty()) fullpath += uri_encode(path, false);

    if (!httpoptions.empty()) {
      fullpath += '?' + OptionString(httpoptions, '&', true);
    }

    if (!ldapattributes.empty() || (ldapscope != base) || !ldapfilter.empty()) {
      fullpath += '?' + AttributeString(ldapattributes, ',', true);
    }

    if ((ldapscope != base) || !ldapfilter.empty()) {
      switch (ldapscope) {
      case base:
        fullpath += "?base";
        break;

      case onelevel:
        fullpath += "?one";
        break;

      case subtree:
        fullpath += "?sub";
        break;
      }
    }

    if (!ldapfilter.empty()) fullpath += '?' + uri_encode(ldapfilter, true);

    return fullpath;
  }
