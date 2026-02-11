createDTRPtr(const std::string& source,
                       const std::string& destination,
                       const Arc::UserConfig& usercfg,
                       const std::string& jobid,
                       const uid_t& uid,
                       DTRLogger log) {
    return DTR_ptr(new DTR(source, destination, usercfg, jobid, uid, log));
  }
