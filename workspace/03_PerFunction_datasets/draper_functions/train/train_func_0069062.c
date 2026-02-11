kill(const std::string& jobid) {
    action = "TerminateActivities";
    logger.msg(VERBOSE, "Creating and sending terminate request to %s", rurl.str());

    PayloadSOAP req(arex_ns);
    XMLNode jobref = req.NewChild("bes-factory:" + action).NewChild(XMLNode(jobid));
    WSAHeader(req).Action(BES_FACTORY_ACTIONS_BASE_URL + action);

    XMLNode response;
    if (!process(req, false, response))
      return false;

    if ((std::string)response["Response"]["Terminated"] != "true") {
      logger.msg(ERROR, "Job termination failed");
      return false;
    }

    return true;
  }
