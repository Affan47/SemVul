getAGISInfo() {

    if (!cache_file.empty()) {
      std::string data;
      logger.msg(VERBOSE, "Reading cached AGIS data from %s", cache_file);
      struct stat st;
      if (!FileStat(cache_file, &st, false)) {
        logger.msg(VERBOSE, "Cannot read cached AGIS info from %s, will re-download: %s", cache_file, StrError(errno));
      } else if (Time(st.st_mtime) + info_lifetime < Time()) {
        logger.msg(VERBOSE, "Cached AGIS info is out of date, will re-download");
      } else if (!FileRead(cache_file, data)) {
        logger.msg(VERBOSE, "Cannot read cached AGIS info from %s, will re-download: %s", cache_file, StrError(errno));
      } else {
        return parseAGISInfo(data);
      }
    }
    return parseAGISInfo(downloadAGISInfo());
  }
