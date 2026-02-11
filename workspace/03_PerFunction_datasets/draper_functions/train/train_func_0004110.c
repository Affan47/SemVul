removeFile(SRMClientRequest& creq) {

    PayloadSOAP request(ns);
    XMLNode req = request.NewChild("SRMv2:srmRm").NewChild("srmRmRequest");
    req.NewChild("arrayOfSURLs").NewChild("urlArray") = creq.surl();

    PayloadSOAP *response = NULL;
    DataStatus status = process("", &request, &response);
    if (!status) return status;

    XMLNode res = (*response)["srmRmResponse"]["srmRmResponse"];

    std::string explanation;
    SRMStatusCode statuscode = GetStatus(res["returnStatus"], explanation);

    if (statuscode != SRM_SUCCESS) {
      logger.msg(VERBOSE, explanation);
      delete response;
      return DataStatus(DataStatus::DeleteError, srm2errno(statuscode), explanation);
    }

    logger.msg(VERBOSE, "File %s removed successfully", creq.surl());
    delete response;
    return DataStatus::Success;
  }
