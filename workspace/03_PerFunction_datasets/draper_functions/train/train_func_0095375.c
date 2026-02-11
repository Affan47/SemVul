Check(bool check_meta) {
    PayloadRaw request;
    PayloadRawInterface *inbuf = NULL;
    HTTPClientInfo info;
    AutoPointer<ClientHTTP> client(acquire_client(url));
    if (!client) return DataStatus::CheckError;
    MCC_Status r = client->process("GET", url.FullPathURIEncoded(), 0, 15,
                                  &request, &info, &inbuf);
    PayloadRawInterface::Size_t logsize = 0;
    if (inbuf){
      logsize = inbuf->Size();
      delete inbuf; inbuf = NULL;
    }
    if (!r) {
      client = acquire_new_client(url);
      if(client) r = client->process("GET", url.FullPathURIEncoded(), 0, 15,
                                    &request, &info, &inbuf);
      if (inbuf){
        logsize = inbuf->Size();
        delete inbuf; inbuf = NULL;
      }
      if(!r) return DataStatus(DataStatus::CheckError,r.getExplanation());
    }
    release_client(url,client.Release());
    if ((info.code != 200) && (info.code != 206)) return DataStatus(DataStatus::CheckError, http2errno(info.code), info.reason);
    size = logsize;
    logger.msg(VERBOSE, "Check: obtained size %llu", size);
    modified = info.lastModified;
    logger.msg(VERBOSE, "Check: obtained modification time %s", modified.str());
    return DataStatus::Success;
  }
