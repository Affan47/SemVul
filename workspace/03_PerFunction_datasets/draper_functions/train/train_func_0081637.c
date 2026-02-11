StartWriting(DataBuffer& buf,
                                        DataCallback *space_cb) {
    logger.msg(VERBOSE, "StartWriting");
    if (!writing || turls.empty() || !srm_request || r_handle) {
      logger.msg(VERBOSE, "StartWriting: File was not prepared properly");
      return DataStatus(DataStatus::WriteStartError, EARCLOGIC, "File was not prepared");
    }

    buffer = &buf;


    std::srand(time(NULL));
    int n = (int)((std::rand() * ((double)(turls.size() - 1))) / RAND_MAX + 0.25);
    r_url = turls.at(n);
    r_handle = new DataHandle(r_url, usercfg);

    if (!(*r_handle)) {
      delete r_handle; r_handle = NULL;
      logger.msg(VERBOSE, "TURL %s cannot be handled", r_url.str());
      return DataStatus(DataStatus::WriteStartError, EARCRESINVAL, "Transfer URL cannot be handled");
    }

    (*r_handle)->SetAdditionalChecks(false);
    (*r_handle)->SetSecure(force_secure);
    (*r_handle)->Passive(force_passive);

    logger.msg(INFO, "Redirecting to new URL: %s", (*r_handle)->CurrentLocation().str());
    DataStatus r = (*r_handle)->StartWriting(buf);
    if(!r) {
      delete r_handle;
      r_handle = NULL;
    }
    return r;
  }
