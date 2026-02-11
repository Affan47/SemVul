CreateDirectory(bool with_parents) {

    std::string error;
    SRMClient *client = SRMClient::getInstance(usercfg, url.fullstr(), error);
    if (!client) {
      return DataStatus(DataStatus::CreateDirectoryError, ECONNREFUSED, error);
    }


    SRMClientRequest request(CanonicSRMURL(url));

    logger.msg(VERBOSE, "Creating directory: %s", CanonicSRMURL(url));

    DataStatus res = client->mkDir(request);
    delete client;
    client = NULL;

    return res;
  }
